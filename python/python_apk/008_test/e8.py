import kivy

from kivy.uix.floatlayout import FloatLayout
from kivy.app import App
from kivy.properties import ObjectProperty, StringProperty

class Controller(FloatLayout):
    label_wid = ObjectProperty();
    info = StringProperty();

    def do_action(self):
        self.label_wid.text = 'Button pressed';
        self.info = 'Bye'

class e8App(App):
    def build(self):
        return Controller(info='hello world');

if __name__ == '__main__':
    e8App().run();
