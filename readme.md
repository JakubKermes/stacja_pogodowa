Aby uruchomić server w osobnych oknach wierszu polecenia należy:
1. Uruchomić server laravel (nawiasy dla hostingu)
```
php artisan serve (--port="16311")
```
2. Uruchomić server websocketów (nawiasy dla hostingu)
```
php artisan websockets:serve (--port="16311")
```
3. Renderowanie?
```
npm run dev
```


Aby wywołać event na websockecie należy uruchomić link:
``` URL/test //URL strony - na przykład localhost lokalnie ```  

Ścieżka do strony startowej:
``` test\resources\views\welcome.blade.php ```

Ścieżka do eventu (pobranie danych z bazy SQL):
``` test\app\Events\test.php ``` 

Ścieżka do componentu, aktualizwanego przez websocket:
```test\resources\js\components\ExampleComponent.vue ```
