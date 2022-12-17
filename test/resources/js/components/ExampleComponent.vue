<template>
    <div>
        payload:
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
                if (!this.chart) {
                    const ctx = document.getElementById('myChart').getContext('2d');
                    this.chart = new Chart(ctx, {
                        type: 'line',
                        data: {
                            labels: e.map(item => item.DateTime),
                            datasets: [
                                {
                                    label: 'Temperature',
                                    data: e.map(item => item.Temperature),
                                },
                                {
                                    label: 'Pressure',
                                    data: e.map(item => item.Pressure),
                                },
                                {
                                    label: 'Humidity',
                                    data: e.map(item => item.Humidity),
                                },
                                {
                                    label: 'Lightlevel',
                                    data: e.map(item => item.Lightlevel),
                                },
                            ],
                        },
                    });
                } else {
                    // Check if the data has actually changed
                    if (JSON.stringify(e) != JSON.stringify(this.chart.data)) {
                        // Update the chart with the new data
                        this.chart.data.labels = e.map(item => item.DateTime);
                        this.chart.data.datasets[0].data = e.map(item => item.Temperature);
                        this.chart.data.datasets[1].data = e.map(item => item.Pressure);
                        this.chart.data.datasets[2].data = e.map(item => item.Humidity);
                        this.chart.data.datasets[3].data = e.map(item => item.Lightlevel);
                        this.chart.update({preservation: true});
                    }
                }
            });
    },

};
</script>


