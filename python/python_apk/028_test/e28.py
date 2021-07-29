import kivy

from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.floatlayout import FloatLayout

class MyW(Widget):
    def __init__(self, **kwargs):
        super(MyW, self).__init__(**kwargs);
        self.MyW1_name = MyW1();
        self.add_widget(self.MyW1_name);

class MyW1(FloatLayout):
    def __init__(self, **kwargs):
        super(MyW1, self).__init__(**kwargs);
        self.size = (300, 300);

class e28App(App):
    def build(self):
        return MyW();

if __name__ == "__main__":
    e28App().run();
