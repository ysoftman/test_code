# coding: utf-8
# ysoftman
# Machine Learning Recipes with Josh Gordon
# pipeline -> https://www.youtube.com/watch?v=84gqSbLcBFE
# https://www.youtube.com/watch?v=cSKfRcEDGUs
# sudo pip install sklearn scikit-learn numpy graphviz tensorflow
# pip install --upgrade tensorflow
"""
# tensorflow for poets2(텐서플로우를 쉽게 사용할 수 있는 툴) 다운로드
git clone https://github.com/googlecodelabs/tensorflow-for-poets-2
# 모든 과정은 이곳에서 실행되어야 한다.
cd tensorflow-for-poets-2

# 훈련 데이터(꽃 이미지) 다운로드
curl http://download.tensorflow.org/example_images/flower_photos.tgz -O
mkdir tf_files
tar zx -f flower_photos.tgz -C ./tf_files

# tensorflow 모니터링을 위한 텐서보드 백그라운드로 실행
tensorboard --logdir tf_files/training_summaries &
# 텐서보드 삭제시
pkill -f "tensorboard"

# 환경 설정
IMAGE_SIZE=224
ARCHITECTURE="mobilenet_0.50_${IMAGE_SIZE}"
tensorboard --logdir tf_files/training_summaries &

# 재훈련을 위한 스크립트를 다운 받는다.
wget https://github.com/tensorflow/hub/blob/master/examples/image_retraining/retrain.py

# 다운 받은 꽃이미지로 재 훈련한다.
python -m scripts.retrain \
  --bottleneck_dir=tf_files/bottlenecks \
  --how_many_training_steps=500 \
  --model_dir=tf_files/models/ \
  --summaries_dir=tf_files/training_summaries/"${ARCHITECTURE}" \
  --output_graph=tf_files/retrained_graph.pb \
  --output_labels=tf_files/retrained_labels.txt \
  --architecture="${ARCHITECTURE}" \
  --image_dir=tf_files/flower_photos

# 재훈련된 결과 파일이 생성된것을 알 수 있다.
ls -ahl tf_files/retrained_graph.pb tf_files/retrained_labels.txt

# 분류를 스크립트 다운 받는다.
wget https://github.com/tensorflow/tensorflow/blob/master/tensorflow/examples/label_image/label_image.py

# 데이지 꽃 이미지 하나를 분류해 보자. 데이지 꽃으로 가장 높은 점수가 계산되는것을 알 수 있다.
python -m scripts.label_image \
    --graph=tf_files/retrained_graph.pb  \
    --image=tf_files/flower_photos/daisy/21652746_cc379e0eea_m.jpg

# 장미 꽃 이미지 하나를 분류해 보자. 장미 꽃으로 가장 높은 점수가 계산되는것을 알 수 있다.
python -m scripts.label_image \
    --graph=tf_files/retrained_graph.pb  \
    --image=tf_files/flower_photos/roses/2414954629_3708a1a04d.jpg
"""
