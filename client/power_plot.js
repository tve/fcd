var smoothie = new SmoothieChart({fps:50, millisPerPixel:10, minValue: 0, maxValue: 10, maxScaleValue:1, scaleSmoothing:0}); // interpolation: "line"});
smoothie.streamTo(document.getElementById("power_plot"), 500);

// Data
var line1 = new TimeSeries();
var line2 = new TimeSeries();

// Add a random value to each line every second
// setInterval(function() {
//  line1.append(new Date().getTime(), Math.random());
//  line2.append(new Date().getTime(), Math.random());
//}, 1000);

// Add to SmoothieChart
//smoothie.addTimeSeries(line1);
//smoothie.addTimeSeries(line2);

var smoothie = new SmoothieChart({
  grid: { strokeStyle:'rgb(125, 0, 0)', fillStyle:'rgb(60, 0, 0)',
          lineWidth: 1, millisPerLine: 250, verticalSections: 6, },
  labels: { fillStyle:'rgb(60, 0, 0)' }
});
smoothie.addTimeSeries(line1, {strokeStyle:'rgb(0, 255, 1)', fillStyle:'rgba(255, 255, 0, 255)', lineWidth:3 });
//smoothie.addTimeSeries(line2,
//  { strokeStyle:'rgb(255, 0, 255)', fillStyle:'rgba(255, 0, 255, 0.3)', lineWidth:3 });
