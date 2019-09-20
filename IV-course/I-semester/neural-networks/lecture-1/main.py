from keras.models import Sequential
from keras.layers import Dense
from ann_visualizer.visualize import ann_viz
import plotly.graph_objects as go
import plotly as py
import numpy as np


def func(x: float) -> float:
    return x ** 2 + x - 10


if __name__ == '__main__':
    # 1st task
    fig = go.Figure(data=go.Scatter(x=np.linspace(-10, 10), y=func(np.linspace(-10, 10)), mode='lines'))
    fig.update_xaxes(title_text='x')
    fig.update_yaxes(title_text='f(x)')
    py.offline.plot(fig, filename='line.html', auto_open=False)
    # 2nd task
    a = np.array([[3, 1], [1, 2]])
    b = np.array([9, 8])
    x = np.linalg.solve(a, b)
    print(np.allclose(np.dot(a, x), b))
    # 3rd task
    model = Sequential()
    model.add(Dense(4, input_dim=5, activation='relu'))
    model.add(Dense(2, activation='sigmoid'))
    ann_viz(model, title="My first neural network", view=False)
