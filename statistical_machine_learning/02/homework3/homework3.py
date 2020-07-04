import numpy as np

def load_data():
    train_list = []
    test_list = []
    for i in range(10):
        train_list.append(np.loadtxt('data/digit_train{}.csv'.format(i), delimiter=','))
        test_list.append(np.loadtxt('data/digit_test{}.csv'.format(i), delimiter=','))
    train = np.stack(train_list)
    test = np.stack(test_list)
    return train, test

def estimate(train, test):
    mean = train.mean(axis = 1).T
    cov = np.array([np.cov(array.T) for array in train]).mean(axis = 0)
    cov_inv = np.linalg.inv(cov)
    result = (mean.T.dot(cov_inv).dot(test.transpose(1, 2, 0)).T - mean.T.dot(cov_inv).dot(mean / 2).diagonal()).argmax(axis = 2)
    return result

def show_result(result):
    confusion_matrix = np.apply_along_axis(np.bincount, 1, result, None, 10)
    print('accuracy:,', confusion_matrix.diagonal().sum() / confusion_matrix.sum())
    print('confusion matrix:')
    print(confusion_matrix)

train, test = load_data()
result = estimate(train, test)
show_result(result)
