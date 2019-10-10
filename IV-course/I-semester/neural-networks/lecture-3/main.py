import numpy as np


def function(arg1, arg2):
    return 2 * arg1 + arg2


def hard_limit(arg):
    return 1 if arg >= 0 else 0


def loss(value, actual_value):
    return (value - actual_value) ** 2


def loss_grade(value, actual_value):
    return -2 * (value - actual_value)


def make_iterations(train_x, train_y, count):
    weights = np.array([0, 0]).reshape(2, 1)
    bias = 0
    learn_rate = 0.2
    for itr in range(count):
        average_weights = np.array([[0.0], [0.0]])
        for ind in range(train_x.shape[0]):
            a = np.dot(weights.T, train_x[ind]) + bias
            gradient = loss_grade(train_y[ind], a)
            delta = learn_rate * train_x[ind] * gradient
            average_weights += delta
        weights = weights - average_weights / train_x.shape[0]

    print("Training, number of epoch", count)
    for ind in range(train_x.shape[0]):
        a = np.dot(weights.T, train_x[ind]) + bias
        print("My result", a[0][0], "actual result", train_y[ind])


def update_state(xk, sk, wx, w_rec):
    return xk * wx + sk * w_rec


def forward_states(x, wx, w_rec):
    sum_ar = np.zeros((x.shape[0], x.shape[1] + 1))
    for k in range(0, x.shape[1]):
        # S[k] = S[k-1] * wRec + X[k] * wx
        sum_ar[:, k + 1] = update_state(x[:, k], sum_ar[:, k], wx, w_rec)
    return sum_ar


def mean_loss(y, test):
    return np.mean((test - y) ** 2)


def output_gradient(y, test):
    return 2. * (y.reshape(y.shape[0], 1) - test)


def backward_gradient(x, s, grad_out, w_rec):
    # Initialise the array that stores the gradients of the loss with 
    #  respect to the states.
    grad_over_time = np.zeros((x.shape[0], x.shape[1] + 1))
    grad_over_time[:, -1] = grad_out.reshape(4)
    # Set the gradient accumulations to 0
    wx_grad = 0
    w_rec_grad = 0
    for k in range(x.shape[1], 0, -1):
        # Compute the parameter gradients and accumulate the results.
        wx_grad += np.sum(np.mean(grad_over_time[:, k] * x[:, k - 1], axis=0))
        w_rec_grad += np.sum(np.mean(grad_over_time[:, k] * s[:, k - 1]), axis=0)
        # Compute the gradient at the output of the previous layer
        grad_over_time[:, k - 1] = grad_over_time[:, k] * w_rec
    return (wx_grad, w_rec_grad), grad_over_time


def update_propagation(x, t, w, w_prev_sign, w_delta, eta_param, eta_num):
    # Perform forward and backward pass to get the gradients
    s = forward_states(x, w[0], w[1])
    grad_out = output_gradient(s[:, -1], t)
    w_grads, _ = backward_gradient(x, s, grad_out, w[1])
    w_sign = np.sign(w_grads)  # Sign of new gradient
    # Update the Delta (update value) for each weight 
    #  parameter separately
    for itr, _ in enumerate(w):
        if w_sign[itr] == w_prev_sign[itr]:
            w_delta[itr] *= eta_param
        else:
            w_delta[itr] *= eta_num
    return w_delta, w_sign


if __name__ == '__main__':
    # 1st task
    make_iterations(np.array([[[-1], [1]], [[-1 / 3], [1 / 4]], [[1 / 2], [0]], [[1 / 6], [2 / 3]]]),
                    np.array([-1, -5 / 12, 1, 1]),
                    1)

    make_iterations(np.array([[[-1], [1]], [[-1 / 3], [1 / 4]], [[1 / 2], [0]], [[1 / 6], [2 / 3]]]),
                    np.array([-1, -5 / 12, 1, 1]),
                    30)
    # 2nd task
    eta_p = 1.2
    eta_n = 0.5

    # Set initial parameters
    W = [1, 1]  # [wx, wRec]
    W_delta = [0.01, 0.01]  # Update values (Delta) for W
    W_sign = [0, 0]  # Previous sign of W

    X = np.array([-0.5, 1 / 3, 1 / 5, 0.25]).reshape(4, 1)
    t_val = np.array([-1, 1.6, 11 / 15, 7 / 10]).reshape(4, 1)

    ls_of_ws = [(W[0], W[1])]  # List of weights to plot
    # Iterate over 50 iterations
    for it in range(50):
        # Get the update values and sign of the last gradient
        W_delta, W_sign = update_propagation(X, t_val, W, W_sign, W_delta, eta_p, eta_n)
        # Update each weight parameter separately
        for i, _ in enumerate(W):
            W[i] -= W_sign[i] * W_delta[i]
        ls_of_ws.append((W[0], W[1]))  # Add weights to list to plot

    print(f'Final weights are: wx = {W[0]:.4f},  wRec = {W[1]:.4f}')

    test_input = X
    test_output = forward_states(X, W[0], W[1])[:, -1]
    sum_test_input = t_val
    print("Target", t_val.reshape(-1), ", model", test_output)
