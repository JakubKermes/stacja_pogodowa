Aby uruchomić server, w osobnych oknach wierszu polecenia należy:
1. Uruchomić server laravel
```
php artisan serve
```
2. Uruchomić server websocketów (nawiasy dla hostingu)
```
php artisan websockets:serve
```
3. Renderować
```
npm run dev
```


Aby wywołać event na websockecie należy uruchomić link:
``` URL/test //URL strony - na przykład localhost lokalnie ```  

Ścieżka do strony startowej:
``` test\resources\views\welcome.blade.php ```

Ścieżka do eventu (pobranie danych z bazy SQL):
``` test\app\Events\test.php ``` 

Ścieżka do componentu, aktualizowanego przez websocket:
```test\resources\js\components\ExampleComponent.vue ```

Tip:
aby przenieść projekt na inny komputer, skorzystaj z[poradnika](https://stackoverflow.com/questions/32697861/moving-laravel-project-between-computers)
