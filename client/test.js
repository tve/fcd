
var num_err = 0;
var aaa;

$(document).ready(function(){
   $("h3").click(function(event){
     alert("Thanks for visiting!");
   });
 });


function fetchData() {
   $.ajax({
      url:      'http://localhost:4000',
      method:   'GET',
      dataType: 'script',
      success:  function(series) {
//	  line1.append(series.x, series.y);
	  line1.append(new Date().getTime(), aaa.y);
//	  document.getElementById("var_title").innerHTML = 'got ' + aaa.x + ' and ' + aaa.y;
      },
       error: function(a, b, c) {
	   document.getElementById("var_title").innerHTML = num_err + ' Got error in fetch: ' + b + ':' + c;
num_err = num_err + 1;

       }
   });

   setTimeout(fetchData, 50);
}

fetchData();

