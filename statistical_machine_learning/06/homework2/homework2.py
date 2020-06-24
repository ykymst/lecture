import csv
import numpy as np

np.random.seed(1)

def load_data_from_csv(filename):
    data = list()
    y = list()
    for i in range(10):
        with open(filename.format(i), 'r') as f:
            reader = csv.reader(f, delimiter=',')
            data_i = np.asarray([[float(v) for v in line] for line in reader])
            y.append([i for _ in range(len(data_i))])
            data.append(data_i)
    return data, y

def knn(train_x, train_y, test_x, k_list):
    train_x = train_x.astype(np.float32)
    test_x = test_x.astype(np.float32)
    dist_matrix = np.sqrt(np.sum((train_x[None] - test_x[:, None]) ** 2,
                                 axis=2))
    sorted_index_matrix = np.argsort(dist_matrix, axis=1)
    ret_matrix = []
    for k in k_list:
        knn_label = train_y[sorted_index_matrix[:, :k]]
        prediction = np.argmax(
            np.apply_along_axis(np.bincount, 1, knn_label, None, 10), axis=1)
        ret_matrix.append(prediction)
    return np.stack(ret_matrix, axis=0)  # shape == (len(k_list), len(test_x))

def cross_validation(x, y, n_fold=5):
    n = len(x)
    k_list = np.arange(1, 11, 1)
    index = np.random.permutation(np.arange(n))
    batch_size = len(x) // n_fold
    correct_sum = np.zeros(len(k_list))
    for i in range(n_fold):
        val_begin, val_end = i * batch_size, (i + 1) * batch_size
        train_x = np.concatenate([x[index[:val_begin]], x[index[val_end:]]])
        train_y = np.concatenate([y[index[:val_begin]], y[index[val_end:]]])
        val_x = x[index[val_begin:val_end]]
        val_y = y[index[val_begin:val_end]]
        res_matrix = knn(train_x, train_y, val_x, k_list)
        correct_sum += np.sum(np.where(res_matrix == val_y[:, None], 1, 0),
                              axis=0)
    best_k = k_list[np.argmax(correct_sum)]
    return best_k

def build_confusion_matrix(train_x, train_y, test_x, test_y, best_k):
    confusion_matrix = np.zeros((10, 10), dtype=np.int64)
    for i in range(10):
        data = test_x[test_y == i]
        prediction = knn(train_x, train_y, data, [best_k])
        confusion_matrix[i] = np.bincount(prediction.squeeze(), None, 10)
    accuracy = np.trace(confusion_matrix) / len(test_x)
    return accuracy, confusion_matrix

train_data, train_label = load_data_from_csv('digit_train{}.csv')
x, y = np.concatenate(train_data), np.concatenate(train_label)
best_k = cross_validation(x, y, n_fold=5)
print('best_k: {}'.format(best_k))

test_data, test_label = load_data_from_csv('digit_test{}.csv')
test_x, test_y = np.concatenate(test_data), np.concatenate(test_label)
accuracy, confusion_matrix = build_confusion_matrix(x, y, test_x, test_y,
                                                    best_k)
print('accuracy: {}'.format(accuracy))
print('confusion matrix:')
print(confusion_matrix)
