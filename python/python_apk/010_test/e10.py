import kivy

from kivy.app import App
from kivy.uix.widget import Widget

class MyW(Widget):
    def on_touch_down(self, touch):
        if 'button' in touch.profile:
            self.ids.button1.text = touch.button;

        if 'pressure' in touch.profile:
            self.ids.label1.text = str(touch.profile);

class e10App(App):

    def build(self):
        return MyW();

if __name__ == "__main__":
    e10App().run();
