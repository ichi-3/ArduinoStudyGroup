<!DOCTYPE html>
<html lang="ja">
<head>
	<meta charset="utf-8">
	<title></title>
	<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
	<?php
		$seat_id = $_GET['seat_id'];
	?>
	<div id="main">
		<svg id="graph"></svg>
	</div>
	<script src="jquery-2.1.3.min.js"></script>
	<script src="d3.min.js"></script>
	<script>
		var data = loadJsonFromPHP("database/get_temps.php?seat_id="+<?php echo '"'.$seat_id.'"'; ?>);

		var dataSet = [];
		$.each(data, function(key, val)
		{
			dataSet.push(val['temp']);
		});

		var bar_height = 20;
		var bar_interval = 5;
		var lbl_size = 9;

		var graph = d3.select('#graph')
		.selectAll('rect')
		.data(dataSet)
		.enter();

		graph.append('rect')
		.attr('x', 0)
		.attr('y', function(d, i)
		{
			return i * (bar_height + bar_interval);
		})
		.attr('height', bar_height+"px")
		.attr('width', "0px")
		.transition()
		.duration(1000)
		.attr('width', function(d, i)
		{
			return d + "px";
		});

		graph.append('text')
		.attr('class', 'lbl')
		.attr('fill', 'white')
		.attr('dx', function(d, i)
		{
			return 0;
		})
		.attr('dy', function(d, i)
		{
			return (i * (bar_height + bar_interval)) + lbl_size + lbl_size/2;
		})
		.text(function(d)
		{
			return d/10 + "℃";
		});

		$('#graph')
		.css('height', dataSet.length * (bar_height + bar_interval));

		/*---------------------------------------------------------
		 * ajaxを利用してJSONデータを取得する
		---------------------------------------------------------*/
		function loadJsonFromPHP(phpname)
		{
			var json = null;
			$.ajax(
			{
				url       : phpname
				,type     : 'GET'
				,async    : false
				,dataType : 'json'
				,cache    : false
				,success  : function(data)
				{
					json = data;
				}
			});
			return json;
		}

	</script>
</body>
</html>