from math import cos, sin, atan
from matplotlib import pyplot
import numpy as np


class Neuron:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def draw(self, neuron_radius, layer, initial):
        circle = pyplot.Circle((self.x, self.y), radius=neuron_radius, fill=False)
        pyplot.gca().add_patch(circle)
        if layer == 0:
            pyplot.text(self.x - 4, self.y - 8, initial, fontsize=10)


class Layer:
    def __init__(self, network, number_of_neurons, number_of_neurons_in_widest_layer):
        self.vertical_distance_between_layers = 20
        self.horizontal_distance_between_neurons = 20
        self.neuron_radius = 6
        self.number_of_neurons_in_widest_layer = number_of_neurons_in_widest_layer
        self.previous_layer = self.__get_previous_layer(network)
        self.y = self.__calculate_layer_y_position()
        self.neurons = self.__intialise_neurons(number_of_neurons)

    def __intialise_neurons(self, number_of_neurons):
        neurons = []
        x = self.__calculate_left_margin_so_layer_is_centered(number_of_neurons)
        for iteration in range(number_of_neurons):
            neuron = Neuron(x, self.y)
            neurons.append(neuron)
            x += self.horizontal_distance_between_neurons
        return neurons

    def __calculate_left_margin_so_layer_is_centered(self, number_of_neurons):
        return self.horizontal_distance_between_neurons * (
                self.number_of_neurons_in_widest_layer - number_of_neurons) / 2

    def __calculate_layer_y_position(self):
        if self.previous_layer:
            return self.previous_layer.y + self.vertical_distance_between_layers
        else:
            return 0

    def __get_previous_layer(self, network):
        if len(network.layers) > 0:
            return network.layers[-1]
        else:
            return None

    def __line_between_two_neurons(self, neuron1, neuron2):
        angle = atan((neuron2.x - neuron1.x) / float(neuron2.y - neuron1.y))
        x_adjustment = self.neuron_radius * sin(angle)
        y_adjustment = self.neuron_radius * cos(angle)
        line = pyplot.Line2D((neuron1.x - x_adjustment, neuron2.x + x_adjustment),
                             (neuron1.y - y_adjustment, neuron2.y + y_adjustment))
        pyplot.gca().add_line(line)

    def draw(self, layerType=0, initial=[]):
        for iter in range(0, len(self.neurons)):
            self.neurons[iter].draw(self.neuron_radius, layerType, initial[iter])
            if self.previous_layer:
                for previous_layer_neuron in self.previous_layer.neurons:
                    self.__line_between_two_neurons(self.neurons[iter], previous_layer_neuron)
        # write Text
        x_text = self.number_of_neurons_in_widest_layer * self.horizontal_distance_between_neurons
        if layerType == 0:
            pyplot.text(x_text, self.y, 'Input Layer', fontsize=18)
        elif layerType == -1:
            pyplot.text(x_text, self.y, 'Output Layer', fontsize=18)
        else:
            pyplot.text(x_text, self.y, 'Hidden Layer ' + str(layerType), fontsize=18)


class NeuralNetwork:
    def __init__(self, number_of_neurons_in_widest_layer):
        self.number_of_neurons_in_widest_layer = number_of_neurons_in_widest_layer
        self.layers = []
        self.layertype = 0

    def add_layer(self, number_of_neurons):
        layer = Layer(self, number_of_neurons, self.number_of_neurons_in_widest_layer)
        self.layers.append(layer)

    def draw(self, initial):
        pyplot.figure()
        for i in range(len(self.layers)):
            layer = self.layers[i]
            if i == len(self.layers) - 1:
                i = -1
            layer.draw(i, initial)
        pyplot.axis('scaled')
        pyplot.axis('off')
        pyplot.title('Neural Network architecture', fontsize=15)
        pyplot.show()


class DrawNN:
    def __init__(self, neural_network, initial):
        self.neural_network = neural_network
        self.initial = initial

    def draw(self):
        widest_layer = max(self.neural_network)
        network = NeuralNetwork(widest_layer)
        for l in self.neural_network:
            network.add_layer(l)
        network.draw(self.initial)


class CNeuron:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def draw(self, neuron_radius, layer, initial):
        circle = pyplot.Circle((self.x, self.y), radius=neuron_radius, fill=False)
        pyplot.gca().add_patch(circle)
        if layer == 0:
            pyplot.text(self.x - 4, self.y - 8, initial, fontsize=10)


class CLayer:
    def __init__(self, network, number_of_neurons, number_of_neurons_in_widest_layer):
        self.vertical_distance_between_layers = 20
        self.horizontal_distance_between_neurons = 20
        self.neuron_radius = 6
        self.number_of_neurons_in_widest_layer = number_of_neurons_in_widest_layer
        self.previous_layers = self.__get_previous_layers(network)
        self.y = self.__calculate_layer_y_position()
        self.neurons = self.__intialise_neurons(number_of_neurons)

    def __intialise_neurons(self, number_of_neurons):
        neurons = []
        x = self.__calculate_left_margin_so_layer_is_centered(number_of_neurons)
        for iteration in range(number_of_neurons):
            neuron = CNeuron(x, self.y)
            neurons.append(neuron)
            x += self.horizontal_distance_between_neurons
        return neurons

    def __calculate_left_margin_so_layer_is_centered(self, number_of_neurons):
        return self.horizontal_distance_between_neurons * (
                self.number_of_neurons_in_widest_layer - number_of_neurons) / 2

    def __calculate_layer_y_position(self):
        if self.previous_layers:
            if len(self.previous_layers) > 0:
                return self.previous_layers[-1].y + self.vertical_distance_between_layers
            else:
                return 0
        else:
            return 0

    def __get_previous_layers(self, network):
        if len(network.layers) > 0:
            return network.layers
        else:
            return None

    def __line_between_two_neurons(self, neuron1, neuron2):
        angle = atan((neuron2.x - neuron1.x) / float(neuron2.y - neuron1.y))
        x_adjustment = self.neuron_radius * sin(angle)
        y_adjustment = self.neuron_radius * cos(angle)
        line = pyplot.Line2D((neuron1.x - x_adjustment, neuron2.x + x_adjustment),
                             (neuron1.y - y_adjustment, neuron2.y + y_adjustment))
        pyplot.gca().add_line(line)

    def draw(self, layerType=0, initial=[]):
        for iter in range(0, len(self.neurons)):
            self.neurons[iter].draw(self.neuron_radius, layerType, initial[iter])
            if self.previous_layers and len(self.previous_layers) > 0:
                for layer in self.previous_layers[:layerType]:
                    for previous_layer_neuron in layer.neurons:
                        self.__line_between_two_neurons(self.neurons[iter], previous_layer_neuron)
        # write Text
        x_text = self.number_of_neurons_in_widest_layer * self.horizontal_distance_between_neurons
        if layerType == 0:
            pyplot.text(x_text, self.y, 'Input Layer', fontsize=18)
        elif layerType == -1:
            pyplot.text(x_text, self.y, 'Output Layer', fontsize=18)
        else:
            pyplot.text(x_text, self.y, 'Hidden Layer ' + str(layerType), fontsize=18)


class CNeuralNetwork:
    def __init__(self, number_of_neurons_in_widest_layer):
        self.number_of_neurons_in_widest_layer = number_of_neurons_in_widest_layer
        self.layers = []
        self.layertype = 0

    def add_layer(self, number_of_neurons):
        layer = CLayer(self, number_of_neurons, self.number_of_neurons_in_widest_layer)
        self.layers.append(layer)

    def draw(self, initial):
        pyplot.figure()
        for i in range(len(self.layers)):
            layer = self.layers[i]
            if i == len(self.layers) - 1:
                i = -1
            layer.draw(i, initial)
        pyplot.axis('scaled')
        pyplot.axis('off')
        pyplot.title('Neural Network architecture', fontsize=15)
        pyplot.show()


class DrawCNN:
    def __init__(self, neural_network, initial):
        self.neural_network = neural_network
        self.initial = initial

    def draw(self):
        widest_layer = max(self.neural_network)
        network = CNeuralNetwork(widest_layer)
        for l in self.neural_network:
            network.add_layer(l)
        network.draw(self.initial)


if __name__ == '__main__':
    # 1st task
    network = DrawNN([3, 3, 1], [[1, 3], [3, 4], [4, 5]])
    network.draw()

    network = DrawNN([3, 3, 3, 3, 1], [[1, 2], [3, 4, 5], [6, 7, 8, 9, 0]])
    network.draw()

    # 2nd task
    network = DrawCNN([1, 3, 3, 3, 1], [[1, 2], [3, 4], [5, 6]])
    network.draw()

    network = DrawNN([3, 3, 3, 3, 1], [[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    network.draw()

    # 3rd task
    p = np.array([1, 0])
    w = np.array([-1])
    b = 1
    print(p * w + b)
    print("W = ", w[0])
    print("b = ", b)

    p1 = np.array([1, 1])
    p2 = np.array([0, 1])
    w = np.array([2, 1])
    b = np.array([-1])
    a1 = np.sum(np.dot(p1, w[0])) + b
    a2 = np.sum(np.dot(p2, w[1])) + b
    print("Result, w = [", w[0], ",", w[1], "], b =", b[0])
    print("If at least one component of p1 will be non zero"
          " then result will be non zero and hard limit will be 1, logic sum")
    print("If at least one component of p2 will be zero"
          " then result will be non positive and hard limit will be 0, logic multiply")
