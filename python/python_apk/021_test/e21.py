import kivy

from kivy.app import App
from kivy.uix.widget import Widget

class MyW(Widget):

    def __init__(self, **kwargs):
        super(MyW, self).__init__(**kwargs);
        self.register_event_type('on_swipe');

    def on_swipe(self, value):
        if self.ids.button1.text != 'hello':
            self.ids.label1.text = 'hello1';

    def do_something(self, value):
        self.dispatch('on_swipe', value);

    def on_touch_down(self, touch):
        self.ids.button1.text = 'xxxx';
        self.do_something('text');

class e21App(App):

    def build(self):
        return MyW();

if __name__ == "__main__":
    e21App().run();
