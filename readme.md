To run the server, in separate command prompt windows:
1.Start laravel server
```
php artisan serve
```
2.Start the websocket server
```
php artisan websockets:serve
```
3.Start the development server
```
npm run dev
```


To call an event on the websocket, run the link:
``` URL/test //URL strony - na przykład localhost lokalnie ```  

Path to the home page:
``` test\resources\views\welcome.blade.php ```

Path to the event (downloading data from the SQL database):
``` test\app\Events\test.php ``` 

Path to the component, updated by websocket:
```test\resources\js\components\ExampleComponent.vue ```

Tip:
To transfer a project to another computer, use [the guide](https://stackoverflow.com/questions/32697861/moving-laravel-project-between-computers)
