Aby uruchomić server w osobnych oknach wierszu polecenia:
php artisan serve //uruchomienie servera laravel
php artisan websockets:serve //uruchomienie servera websocketów
npm run dev //rednderowanie?

Aby wywołać event na websockecie należy uruchomić link:
URL/test //URL strony na przykład localhost lokalnie

test\resources\views\welcome.blade.php - ścieżka do strony startowej
test\app\Events\test.php - ścieżka do eventu (pobranie danych z bazy SQL)
test\resources\js\components\ExampleComponent.vue - ścieżka do componentu 
aktualizwanego przez websocket, rysuje wykres (na razie nie działa rysowanie)

przeniesieni projektu na inny komputer według poradnika:
https://stackoverflow.com/questions/32697861/moving-laravel-project-between-computers
