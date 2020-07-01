import numpy as np

# load data
train_list = []
test_list = []
for i in range(10):
    train_list.append(np.loadtxt('data/digit_train{}.csv'.format(i), delimiter=','))
    test_list.append(np.loadtxt('data/digit_test{}.csv'.format(i), delimiter=','))
train = np.stack(train_list)
test = np.stack(test_list)

# estimate
mean = train.mean(axis = 1).T
cov = np.array([np.cov(array.T) for array in train]).mean(axis = 0)
cov_inv = np.linalg.inv(cov)
result = (mean.T.dot(cov_inv).dot(test.transpose(1, 2, 0)).T - mean.T.dot(cov_inv).dot(mean / 2).diagonal()).argmax(axis = 2)

# show result
print((np.tile(np.arange(10).T, (200, 10, 1)).T == result).sum(axis = 2))
