from keras.models import Sequential
from keras.layers import Dense
from ann_visualizer.visualize import ann_viz

if __name__ == '__main__':
    model = Sequential()
    model.add(Dense(4, input_dim=5, activation='relu'))
    model.add(Dense(2, activation='sigmoid'))
    ann_viz(model, title="My first neural network")
