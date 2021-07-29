import kivy

from kivy.app import App
from kivy.uix.widget import Widget

def my_callback(value, *args):
    print("hello, I got an event!",args);

class MyW(Widget):

    def __init__(self, **kwargs):
        super(MyW, self).__init__(**kwargs);
        self.register_event_type('on_swipe');

    def on_swipe(self, value):
        self.ids.label1.text = str(value);

    def do_something(self, value):
        if self.ids.button1.text != 'hello':
            self.dispatch('on_swipe', value);

    def on_touch_down(self, touch):
        #self.bind(on_swipe=my_callback);
        if touch.is_double_tap:
            self.ids.button1.text = 'xxx';
            self.do_something('test double');
        if touch.is_triple_tap:
            self.ids.button1.text = 'hellooo';
            self.do_something('test triple');

class e22App(App):

    def build(self):
        return MyW();

if __name__ == "__main__":
    e22App().run();
