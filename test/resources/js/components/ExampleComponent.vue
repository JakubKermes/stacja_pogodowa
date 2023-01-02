<template>
    <div>
        <div class="_2-col just-l">Wykres:</div>
        <div class="_2-col just-r">
            <form method="post">
                <input type="button" value="1 dzień" name="d-1">
                <input type="button" value="7 dzień" name="d-7">
            </form>
        </div>
    </div>
    <div>        
        <canvas id="myChart" width="400" height="400"></canvas>
    </div>
</template>

<script>
import {Chart} from 'chart.js/auto';
// const Chart = require('chart.js');
export default {
    data() {
        return {
            chart: null,
        };
    },
    mounted() {
        Echo.channel('test')
            .listen('test', (e) => {
                console.log(JSON.stringify(e));
                const DateTime = [];
                const Temperature = [];
                const Pressure = [];
                const Humidity = [];
                const LightLevel = [];
                e.forEach(function (row) {
                    console.log(row.DateTime);
                    DateTime.push(row.DateTime);
                    console.log(row.Temperature);
                    Temperature.push(row.Temperature);
                    console.log(row.Pressure);
                    Pressure.push(row.Pressure);
                    console.log(row.Humidity);
                    Humidity.push(row.Humidity);
                    console.log(row.Lightlevel);
                    LightLevel.push(row.Lightlevel);
                });
                if (!this.chart) {
                    const ctx = document.getElementById('myChart').getContext('2d');
                    this.chart = new Chart(ctx, {
                        type: 'line',
                        data: {
                            labels: DateTime,

                            datasets: [
                                {
                                    label: 'Temperature',
                                    data: Temperature,
                                },
                                {
                                    label: 'Pressure',
                                    data: Pressure,
                                },
                                {
                                    label: 'Humidity',
                                    data: Humidity,
                                },
                                {
                                    label: 'Light level',
                                    data: LightLevel,
                                },
                            ],
                        },
                        options: {
                            scales:{
                                xAxes: [{
                                    type: 'time',
                                    time: {
                                        unit: 'minute',
                                        displayFormats: {
                                            minute: 'HH:mm'
                                        }
                                    }
                                }]
                            }
                        }
                    });
                } else {
                    // Check if the data has actually changed
                    if (JSON.stringify(e) != JSON.stringify(this.chart.data)) {
                        // Update the chart with the new data
                        this.chart.data.labels = DateTime;
                        this.chart.data.datasets[0] = Temperature;
                        this.chart.data.datasets[1] = Pressure;
                        this.chart.data.datasets[2] = Humidity;
                        this.chart.data.datasets[3] = LightLevel;
                        this.chart.update({preservation: true});
                    }
                }
            });
    },
};
</script>
