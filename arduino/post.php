<?php
if(isset($_GET["temperature"])) {
   $temperature = $_GET["temperature"]; 
}

if(isset($_GET["pressure"])) {
   $pressure = $_GET["pressure"]; 
}

if(isset($_GET["humidity"])) {
   $humidity = $_GET["humidity"]; 
}

if(isset($_GET["lightlevel"])) {
   $lightlevel = $_GET["lightlevel"]; 
}

   $servername = "mysql0.small.pl";
   $username = "m2507_pogoda";
   $password = "DreamTeam1";
   $database_name = "m2507_stacja_pogodowa_sobin";

   // Create MySQL connection fom PHP to MySQL server
   $connection = new mysqli($servername, $username, $password, $database_name);
   // Check connection
   if ($connection->connect_error) {
      die("MySQL connection failed: " . $connection->connect_error);
   
}
   $sql = "INSERT INTO pogoda (Temperature, Pressure, Humidity, Lightlevel) VALUES ($temperature, $pressure, $humidity, $lightlevel)";

   if ($connection->query($sql) === TRUE) {
      echo 'New record created successfully';

   } else {

      echo "Error: " . $sql . " => " . $connection->error;
   }

   $connection->close();
?>