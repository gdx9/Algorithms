import numpy as np
import random
import matplotlib.pyplot as plt
#%matplotlib inline

def calc_line_y(x, slope, bias):
    return x * slope + bias

def calc_best_fit_line_params(x,y):
    x_mean = np.average(x)
    y_mean = np.average(y)

    slope = np.sum((x - x_mean) * (y - y_mean)) / np.sum((x - x_mean) ** 2)
    bias = y_mean - slope * x_mean
    return slope,bias

if __name__ == "__main__":
    # generate data with noise
    xy = np.array([
        (n, calc_line_y(n, slope=2.5, bias=30)
        + random.randint(-140,140))# noise
        for n in range(-100, 100, 4)
    ])

    slope,bias = calc_best_fit_line_params(xy[:,0], xy[:,1])
    print("best fir equasion: f(x) = {:.2f} * x + {:.2f}".format(slope, bias))

    min_x = min(xy[:,0]).astype(np.int32)
    max_x = max(xy[:,0]).astype(np.int32)
    min_y = calc_line_y(min_x, slope, bias)
    max_y = calc_line_y(max_x, slope, bias)

    # plot points
    plt.scatter(xy[:,0], xy[:,1])
    # plot line
    plt.plot([min_x, max_x], [min_y, max_y], c='r')
