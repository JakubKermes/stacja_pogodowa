Aby uruchomić server w osobnych oknach wierszu polecenia:
```php artisan serve (--port="16311")```//uruchomienie servera laravel, nawiasy dla hostingu
```php artisan websockets:serve (--port="16311")```//uruchomienie servera websocketów, nawiasy dla hostingu
```npm run dev``` //rednderowanie?

Aby wywołać event na websockecie należy uruchomić link:
```URL/test //URL_strony``` na przykład localhost lokalnie

test\resources\views\welcome.blade.php - ścieżka do strony startowej
test\app\Events\test.php - ścieżka do eventu (pobranie danych z bazy SQL)
test\resources\js\components\ExampleComponent.vue - ścieżka do componentu 
aktualizwanego przez websocket, rysuje wykres (na razie nie działa rysowanie)
