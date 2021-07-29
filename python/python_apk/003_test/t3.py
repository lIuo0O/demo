from kivy.app import App
from kivy.uix.label import Label


class T3(App):
    def build(self):
        self.title = 'python app';
        return Label(text='hello kivy');

if __name__ == "__main__":
	T3().run();
