from kivy.app import App
from kivy.uix.gridlayout import GridLayout
from kivy.uix.label import Label
from kivy.uix.textinput import TextInput
from kivy.config import Config
from kivy import resources

class LoginScreen(GridLayout):

    def __init__(self, **kwargs):
        super(LoginScreen, self).__init__(**kwargs);
        self.cols = 2;
        self.add_widget(Label(text='User Name'));
        self.username = TextInput(multiline=False);
        self.add_widget(self.username);
        self.add_widget(Label(text='password'));
        self.password = TextInput(password=True, multiline=False);
        self.add_widget(self.password);

class MyApp(App):

    def build(self):
        return LoginScreen();

if __name__ == "__main__":
    Config.set('kivy','default_font',['msgothic','D:\L\python3\DroidSansFallback.ttf']);
    Config.write();
    resources.resource_add_path("./container_kvs");
    font1 = resources.resource_find("msgothic.ttc");
    MyApp().run();
