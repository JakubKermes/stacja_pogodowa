<template>
    <div>
        <canvas id="myChart" width="100%" height="100%"></canvas>
    </div>
</template>

<script>
import {Chart} from 'chart.js';

export default {
    name: 'my-component',
    data() {
        return {
            chart: null,
        };
    },
    mounted() {
        this.chart = new Chart(document.getElementById('myChart'), {
            type: 'line',
            data: {
                labels: this.output.map(item => item.DateTime),
                datasets: [
                    {
                        label: 'Temperature',
                        data: this.output.map(item => item.Temperature),
                    },
                    {
                        label: 'Pressure',
                        data: this.output.map(item => item.Pressure),
                    },
                    {
                        label: 'Humidity',
                        data: this.output.map(item => item.Humidity),
                    },
                    {
                        label: 'Lightlevel',
                        data: this.output.map(item => item.Lightlevel),
                    },
                ],
            },
        });
    },
};
</script>
