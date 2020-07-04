import numpy as np
np.random.seed(1)

def load_data():
    train_list = []
    train_label_list = []
    test_list = []
    for i in range(10):
        train_data = np.loadtxt('data/digit_train{}.csv'.format(i), delimiter=',')
        train_list.append(train_data)
        train_label_list.append(np.full(train_data.shape[0], i))
        test_list.append(np.loadtxt('data/digit_test{}.csv'.format(i), delimiter=','))
    train = np.concatenate(train_list)
    train_label = np.concatenate(train_label_list)
    test = np.concatenate(test_list)
    return train, train_label, test

def knn(train, train_label, test, k_list):
    squared_distance = np.sum((train[None] - test[:, None]) ** 2, axis = 2)
    knn_labels = train_label[squared_distance.argsort(axis = 1)]
    prediction = np.array([np.apply_along_axis(np.bincount, 1, knn_labels[:, :k], None, 10).argmax(axis = 1) for k in k_list])
    return prediction

def cross_validation(data, data_label, n_fold = 5, k_max = 10):
    n = len(data)
    index = np.random.permutation(np.arange(n))
    accuracy_list = np.zeros(k_max)
    for i in range(n_fold):
        train_index = np.concatenate([index[:n * i // n_fold], index[n * (i + 1) // n_fold:]])
        validation_index = index[n * i // n_fold:n * (i + 1) // n_fold]
        train = data[train_index]
        train_label = data_label[train_index]
        validation = data[validation_index]
        validation_label = data_label[validation_index]
        prediction = knn(train, train_label, validation, range(1, k_max + 1))
        accuracy_list += (prediction == validation_label).mean(axis = 1)
    best_k = accuracy_list.argmax() + 1
    print('best_k:', best_k)
    return best_k

def show_result(prediction):
    confusion_matrix = np.apply_along_axis(np.bincount, 1, prediction.reshape((10, -1)), None, 10)
    print('accuracy:,', confusion_matrix.diagonal().sum() / confusion_matrix.sum())
    print('confusion matrix:')
    print(confusion_matrix)

train, train_label, test = load_data()
best_k = cross_validation(train, train_label)
prediction = knn(train, train_label, test, [best_k])
show_result(prediction)