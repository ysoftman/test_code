import numpy as np
import matplotlib as plt
import pandas as pd
import seaborn as sb

vector = []
for i in xrange(1000):
    vector.append([np.random.normal(0.0, 0.9), np.random.normal(0.0, 0.9)])
for i in xrange(500):
    vector.append([np.random.normal(3.0, 0.5), np.random.normal(1.0, 0.5)])

df = pd.DataFrame({"x": [v[0] for v in vector], "y": [v[1] for v in vector]})
print df
sb.lmplot("x", "y", data=df, fit_reg=False, size=6)
plt.pyplot.show()
