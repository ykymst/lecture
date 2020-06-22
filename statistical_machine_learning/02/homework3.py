import numpy as np
from scipy.io import loadmat

def estimate_mean(X):
    return np.mean(X, axis=2)

def estimate_cov(X):
    class_num = len(X)
    S = np.zeros((X.shape[1], X.shape[1]))
    n = np.size(X)
    for y in range(class_num):
        ny = np.size(X[y])
        S += ny / n * np.cov(X[y])
    return S


def estimate_log_posterior(X, mean_list, S):
    class_num = len(X)
    result_list = [[] for _ in range(class_num)]
    for i in range(class_num):          # calculate the posterior of the data of class i
        for j in range(class_num):      # calculate the posterior of each data of class i for class j
            result = mean_list[j].T.dot(np.linalg.solve(S, X[i])) - \
                     mean_list[j].T.dot(np.linalg.solve(S, mean_list[j])) / 2
            result_list[i].append(result)
    return np.array(result_list)


# load data
data = loadmat('digit.mat')
train = data['X'].transpose(2, 0, 1)   # train.shape == (10, 256, 500)
test = data['T'].transpose(2, 0, 1)    # test.shape == (10, 256, 200)

# calculate the posterior
mean = estimate_mean(train)
cov = estimate_cov(train)
result = estimate_log_posterior(test, mean, cov)

# show the results
confusion_matrix = np.zeros((10, 10))
for i in range(10):
    prediction = np.argmax(result[i], axis=0)
    for j in range(10):
        confusion_matrix[i][j] = np.sum(prediction == j)

print(confusion_matrix)
