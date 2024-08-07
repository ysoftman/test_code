# coding: utf-8
# ysoftman
# python version : 3.x

"""
word2vec : 구글에서 자연어 처리를 위해 만든 단어들을 벡터에 (수치)표한해 다음에 올 단어를 예측한다.

2013년 발표 논문 : https://papers.nips.cc/paper/5021-distributed-representations-of-words-and-phrases-and-their-compositionality.pdf

프로젝트 : https://code.google.com/archive/p/word2vec/

tensorflow 한글번역 책 : https://legacy.gitbook.com/book/tensorflowkorea/tensorflow-kr/details 

튜토리얼 : https://github.com/tensorflow/tensorflow/blob/master/tensorflow/examples/tutorials/word2vec/word2vec_basic.py

[용어]
CBOW(Continuous Bag-of-Words) : 연속되는(문장에서 빈곳) 단어를 예측하는 모델, 작은 데이터셋에 적합
Skip-Gram : 주어진 단어와 가장 가까운 거리(유사도가 높은) 단어를 선택해서 문장(단어 주위를)을 채워 나가는 모델, 큰 데이터셋에 적합
"""

import os
import urllib.request
import math
import zipfile
import random
import collections
import numpy as np
import tensorflow as tf
from six.moves import xrange
from tensorflow.contrib.tensorboard.plugins import projector


dataset_dir = os.path.dirname(os.path.abspath(__file__))
dataset_dir = os.path.join(dataset_dir, "words-data")
if not os.path.exists(dataset_dir):
    os.mkdir(dataset_dir)

log_dir = os.path.dirname(os.path.abspath(__file__))
log_dir = os.path.join(log_dir, "word2vec-logs")
if not os.path.exists(log_dir):
    os.mkdir(log_dir)


#####

# 1. 데이터 파일 다운로드
url_base = "http://mattmahoney.net/dc/"
data_file = "text8.zip"


def download(file_name):
    file_path = os.path.join(dataset_dir, file_name)

    if os.path.exists(file_path):
        print(os.path.join(dataset_dir, file_name), " exists")
        return

    print("Downloading " + url_base + file_name + " ... ")
    urllib.request.urlretrieve(url_base + file_name, file_path)
    print("Done")


# 데이터 다운로드(약 30MB)
download(data_file)


# 다운로드 데이터 읽기
def read_data(file_name):
    with zipfile.ZipFile(file_name) as f:
        data = tf.compat.as_str(f.read(f.namelist()[0])).split()
    return data


# 17005207 단어가 있어 출력하면 넘 오래 걸린다.
vocabulary = read_data(os.path.join(dataset_dir, data_file))
print("vocabulary size :", len(vocabulary))


#####


# 2. 데이터를 기반으로 사전 만들기, 드문 단언들은 UNK(unknown?) 토큰으로 변경
vocabulary_size = 50000


def build_dataset(words, n_words):
    count = [["UNK", -1]]
    count.extend(collections.Counter(words).most_common(n_words - 1))
    dictionary = dict()
    for word, _ in count:
        dictionary[word] = len(dictionary)
    data = list()
    unk_count = 0
    for word in words:
        index = dictionary.get(word, 0)
        if index == 0:  # dictionary['UNK']
            unk_count += 1
        data.append(index)
    count[0][1] = unk_count
    reversed_dictionary = dict(zip(dictionary.values(), dictionary.keys()))
    return data, count, dictionary, reversed_dictionary


# data : list of codes (integers from 0 to vocabulary_size-1).
#       This is the original text but words are replaced by their codes
# count : map of words(strings) to count of occurrences
# dictionary : map of words(strings) to their codes(integers)
# reverse_dictionary : maps codes(integers) to words(strings)
data, count, dictionary, reverse_dictionary = build_dataset(vocabulary, vocabulary_size)

# 사전 데이터를 만들고 필요없어진 raw vocabulary 는 메모리를 줄이기 위해 삭제한다.
del vocabulary
# 가장 많은 빈도 5개로 다음과 같이 출력된다.
# [['UNK', 418391], ('the', 1061396), ('of', 593677), ('and', 416629), ('one', 411764)]
print("Most common words (+UNK)", count[:5])
print("Sample data", data[:10], [reverse_dictionary[i] for i in data[:10]])


#####


# 3. skip-gram 모델용 훈련 배치 생성
data_index = 0


def generate_batch(batch_size, num_skips, skip_window):
    global data_index
    assert batch_size % num_skips == 0
    assert num_skips <= 2 * skip_window
    batch = np.ndarray(shape=(batch_size), dtype=np.int32)
    labels = np.ndarray(shape=(batch_size, 1), dtype=np.int32)
    span = 2 * skip_window + 1  # [ skip_window target skip_window ]
    buffer = collections.deque(maxlen=span)  # pylint: disable=redefined-builtin
    if data_index + span > len(data):
        data_index = 0
    buffer.extend(data[data_index : data_index + span])
    data_index += span
    for i in range(batch_size // num_skips):
        context_words = [w for w in range(span) if w != skip_window]
        words_to_use = random.sample(context_words, num_skips)
        for j, context_word in enumerate(words_to_use):
            batch[i * num_skips + j] = buffer[skip_window]
            labels[i * num_skips + j, 0] = buffer[context_word]
        if data_index == len(data):
            buffer.extend(data[0:span])
            data_index = span
        else:
            buffer.append(data[data_index])
            data_index += 1
    # Backtrack a little bit to avoid skipping words in the end of a batch
    data_index = (data_index + len(data) - span) % len(data)
    return batch, labels


batch, labels = generate_batch(batch_size=8, num_skips=2, skip_window=1)
for i in range(8):
    print(
        batch[i],
        reverse_dictionary[batch[i]],
        "->",
        labels[i, 0],
        reverse_dictionary[labels[i, 0]],
    )


#####

# 4. skip-gram 그래프 만들기
batch_size = 128
embedding_size = 128  # Dimension of the embedding vector.
skip_window = 1  # How many words to consider left and right.
num_skips = 2  # How many times to reuse an input to generate a label.
num_sampled = 64  # Number of negative examples to sample.

# We pick a random validation set to sample nearest neighbors. Here we limit the
# validation samples to the words that have a low numeric ID, which by
# construction are also the most frequent. These 3 variables are used only for
# displaying model accuracy, they don't affect calculation.
valid_size = 16  # Random set of words to evaluate similarity on.
valid_window = 100  # Only pick dev samples in the head of the distribution.
valid_examples = np.random.choice(valid_window, valid_size, replace=False)

graph = tf.Graph()

with graph.as_default():

    # Input data.
    with tf.name_scope("inputs"):
        train_inputs = tf.placeholder(tf.int32, shape=[batch_size])
        train_labels = tf.placeholder(tf.int32, shape=[batch_size, 1])
        valid_dataset = tf.constant(valid_examples, dtype=tf.int32)

    # Ops and variables pinned to the CPU because of missing GPU implementation
    with tf.device("/cpu:0"):
        # Look up embeddings for inputs.
        with tf.name_scope("embeddings"):
            embeddings = tf.Variable(
                tf.random_uniform([vocabulary_size, embedding_size], -1.0, 1.0)
            )
            embed = tf.nn.embedding_lookup(embeddings, train_inputs)

        # Construct the variables for the NCE loss
        with tf.name_scope("weights"):
            nce_weights = tf.Variable(
                tf.truncated_normal(
                    [vocabulary_size, embedding_size],
                    stddev=1.0 / math.sqrt(embedding_size),
                )
            )
        with tf.name_scope("biases"):
            nce_biases = tf.Variable(tf.zeros([vocabulary_size]))

    # Compute the average NCE loss for the batch.
    # tf.nce_loss automatically draws a new sample of the negative labels each
    # time we evaluate the loss.
    # Explanation of the meaning of NCE loss:
    #   http://mccormickml.com/2016/04/19/word2vec-tutorial-the-skip-gram-model/
    with tf.name_scope("loss"):
        loss = tf.reduce_mean(
            tf.nn.nce_loss(
                weights=nce_weights,
                biases=nce_biases,
                labels=train_labels,
                inputs=embed,
                num_sampled=num_sampled,
                num_classes=vocabulary_size,
            )
        )

    # Add the loss value as a scalar to summary.
    tf.summary.scalar("loss", loss)

    # Construct the SGD optimizer using a learning rate of 1.0.
    with tf.name_scope("optimizer"):
        optimizer = tf.train.GradientDescentOptimizer(1.0).minimize(loss)

    # Compute the cosine similarity between minibatch examples and all
    # embeddings.
    norm = tf.sqrt(tf.reduce_sum(tf.square(embeddings), 1, keepdims=True))
    normalized_embeddings = embeddings / norm
    valid_embeddings = tf.nn.embedding_lookup(normalized_embeddings, valid_dataset)
    similarity = tf.matmul(valid_embeddings, normalized_embeddings, transpose_b=True)

    # Merge all summaries.
    merged = tf.summary.merge_all()

    # Add variable initializer.
    init = tf.global_variables_initializer()

    # Create a saver.
    saver = tf.train.Saver()


#####

# 5. 훈련
num_steps = 100001

with tf.Session(graph=graph) as session:
    # Open a writer to write summaries.
    writer = tf.summary.FileWriter(log_dir, session.graph)

    # We must initialize all variables before we use them.
    init.run()
    print("Initialized")

    average_loss = 0
    for step in xrange(num_steps):
        batch_inputs, batch_labels = generate_batch(batch_size, num_skips, skip_window)
        feed_dict = {train_inputs: batch_inputs, train_labels: batch_labels}

        # Define metadata variable.
        run_metadata = tf.RunMetadata()

        # We perform one update step by evaluating the optimizer op (including it
        # in the list of returned values for session.run()
        # Also, evaluate the merged op to get all summaries from the returned "summary" variable.
        # Feed metadata variable to session for visualizing the graph in
        # TensorBoard.
        _, summary, loss_val = session.run(
            [optimizer, merged, loss], feed_dict=feed_dict, run_metadata=run_metadata
        )
        average_loss += loss_val

        # Add returned summaries to writer in each step.
        writer.add_summary(summary, step)
        # Add metadata to visualize the graph for the last run.
        if step == (num_steps - 1):
            writer.add_run_metadata(run_metadata, "step%d" % step)

        if step % 2000 == 0:
            if step > 0:
                average_loss /= 2000
            # The average loss is an estimate of the loss over the last 2000
            # batches.
            print("Average loss at step ", step, ": ", average_loss)
            average_loss = 0

        # Note that this is expensive (~20% slowdown if computed every 500
        # steps)
        if step % 10000 == 0:
            sim = similarity.eval()
            for i in xrange(valid_size):
                valid_word = reverse_dictionary[valid_examples[i]]
                top_k = 8  # number of nearest neighbors
                nearest = (-sim[i, :]).argsort()[1 : top_k + 1]
                log_str = "Nearest to %s:" % valid_word
                for k in xrange(top_k):
                    close_word = reverse_dictionary[nearest[k]]
                    log_str = "%s %s," % (log_str, close_word)
                print(log_str)
    final_embeddings = normalized_embeddings.eval()

    # Write corresponding labels for the embeddings.
    with open(log_dir + "/metadata.tsv", "w") as f:
        for i in xrange(vocabulary_size):
            f.write(reverse_dictionary[i] + "\n")

    # Save the model for checkpoints.
    saver.save(session, os.path.join(log_dir, "model.ckpt"))

    # Create a configuration for visualizing embeddings with the labels in
    # TensorBoard.
    config = projector.ProjectorConfig()
    embedding_conf = config.embeddings.add()
    embedding_conf.tensor_name = embeddings.name
    embedding_conf.metadata_path = os.path.join(log_dir, "metadata.tsv")
    projector.visualize_embeddings(writer, config)

writer.close()


#####


# 6. 시각화
# pylint: disable=missing-docstring
# Function to draw visualization of distance between embeddings.
def plot_with_labels(low_dim_embs, labels, filename):
    assert low_dim_embs.shape[0] >= len(labels), "More labels than embeddings"
    plt.figure(figsize=(18, 18))  # in inches
    for i, label in enumerate(labels):
        x, y = low_dim_embs[i, :]
        plt.scatter(x, y)
        plt.annotate(
            label,
            xy=(x, y),
            xytext=(5, 2),
            textcoords="offset points",
            ha="right",
            va="bottom",
        )

    plt.savefig(filename)


from sklearn.manifold import TSNE
import matplotlib.pyplot as plt

tsne = TSNE(perplexity=30, n_components=2, init="pca", n_iter=5000, method="exact")
plot_only = 500
low_dim_embs = tsne.fit_transform(final_embeddings[:plot_only, :])
labels = [reverse_dictionary[i] for i in xrange(plot_only)]
plot_with_labels(low_dim_embs, labels, os.path.join(os.path.curdir, "tsne.png"))
