<?php

namespace App\Events;

use Illuminate\Broadcasting\Channel;
use Illuminate\Broadcasting\InteractsWithSockets;
use Illuminate\Broadcasting\PresenceChannel;
use Illuminate\Broadcasting\PrivateChannel;
use Illuminate\Contracts\Broadcasting\ShouldBroadcast;
use Illuminate\Database\MySqlConnection;
use Illuminate\Foundation\Events\Dispatchable;
use Illuminate\Queue\SerializesModels;



class test implements ShouldBroadcast
{
    use Dispatchable, InteractsWithSockets, SerializesModels;

    /**
     * Create a new event instance.
     *
     * @return void
     */
    public function __construct()
    {
        //
    }

    /**
     * Get the channels the event should broadcast on.
     *
     * @return \Illuminate\Broadcasting\Channel|array
     */

    public function broadcastWith()
    {
        $servername = "127.0.0.1";
        $username = "test";
        $password = "";
        $dbname = "stacja_pogodowa_sobin";
        $output = array();

// Create connection
        $conn = new \mysqli($servername, $username, $password, $dbname);

// Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        }
        date_default_timezone_set('Europe/Warsaw');
        $date = new \DateTime();
        $dateback = new \DateTime();
        $dateback->modify('-1 hours') ;

        $datestring = $date->format('Y-m-d H:i:s');
        $datebackstring = $dateback->format('Y-m-d H:i:s');
        $sql = "SELECT * FROM pogoda WHERE DateTime >= '$datebackstring' AND DateTime <= '$datestring'";
        $result = $conn -> query($sql);
        if ($result->num_rows > 0) {
            // output data of each row
            while($row = $result->fetch_assoc()) {
                $DateTime = $row["DateTime"];
                $Temperature = $row["Temperature"];
                $Pressure = $row["Pressure"];
                $Humidity = $row["Humidity"];
                $Lightlevel = $row["Lightlevel"];
                $output[] = array('DateTime'=>$DateTime, 'Temperature'=>$Temperature, 'Pressure'=>$Pressure, 'Humidity'=>$Humidity, 'Lightlevel'=>$Lightlevel);

            }
        } else {
            echo "0 results";
        }
        return [
            $output
        ];
    }
    public function broadcastOn()
    {
        return new Channel('test');
    }
}
?>