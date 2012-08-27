<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf8">
		<script src="http://code.jquery.com/jquery-1.7.2.min.js"></script>
		<script>
		var nowMenu = '';
		$(document).ready(function(){
			$(document).keydown(function(ev){
				console.log(ev);
				$('#KD').html(ev.which);
				if(ev.which!=116)
				   ev.preventDefault();
				if(ev.which == 13){
				   enterClass(3);
				}
				if(ev.which == 8){
				   escapeClass();
				   goMainMenu();
				}
			});
			$(window).bind('popstate', function(e) {
				var state = event.state;
				console.log(state);
  			 //   $('#slider').slideTo(location.pathname)
			    //	alert('aa');
				if(state){

				}else{
				    goMainMenu();
				}
			//	alert('a');
			});
			$("#boardMenu").hide();
			$("#mainMenu > a").live("click",function(event){
			    event.preventDefault();
			    var sel = $(this).attr('href').slice(8);
		 	    var tmp = null;
			    $.each(DATA,function(i,v){
				if(v['tag'][0] === sel && v['cn'].length == 2){
				    var url = 'class/'+sel;
				    history.pushState({ page:url,pichu:true },url,url);
				    tmp = v;
				 
				}
			    });	
			    var tmpData = [];
			    nowMenu = tmp['cn'].slice(1,3);
			    $.each(DATA,function(i,v){
				if(v['cn'].slice(1,2) === nowMenu){
					tmpData.push(v);
				}
			    });
			    console.log(tmpData);

			    var classData = [];
			    $.each(tmpData,function(i,v){
				if(v['cn'][0] == '+'){
					classData.push(v);
				}
			    });


			    replaceMenu($("#mainMenu"),classData);
			    enterClass();	
			});

		});

		function goMainMenu(){
			nowMenu = "";
			var tmpData = [];	
			$.each(DATA,function(i,v){
					if(v['cn'].length === 2){
						tmpData.push(v);
					}
					});
			console.log(tmpData);
			replaceMenu($("#mainMenu"),tmpData);

		}

		function replaceMenu($target,data){
			$target.html('');
			$.each(data,function(i,v){
			var otherInfo = "<ul>";
			    for(var i=1;i < v['tag'].length ; ++i){
			        otherInfo += '<li class="info"> ' + v['tag'][i] + '</li>';	
			    }
			otherInfo += "</ul>"
			$target.append('<a href="./class/' + v['tag'][0] + '">' +
                                '<li>' +
                                        '<span style="margin-left:auto;">' + v['tag'][0] + '</span>' +
					otherInfo +
                                '</li>' +
                                '</a>');
			});

		}


		function enterClass(id){
			//$("#mainMenu").hide();
			$("#boardMenu").show();
		}
		function escapeClass(){
			$("#boardMenu").hide();
			//$("#mainMenu").show();
			history.back();
		}
		</script>
		<style>
		ol.menu{
			list-style-type:none;
		}
	
		ol.menu > a > li{
			width:173px;
			height:173px;
			float:left;
			background:pink;
			margin:10px;
		}
		</style>
		<?php 
			$data = file_get_contents('http://127.0.0.1/newUI/ajax.php');
		?>
		<script>
		var DATA = <?=$data?>;
		</script>
	</head>
	<body>
		分類看板<div id="KD">a</div>
		<span><?=$_SERVER['PATH_INFO']; ?></span> 	
		<?php $argv = explode('/',$_SERVER['PATH_INFO']);?>
		<span><?php print_r($argv);?> </span>
		<ol id="mainMenu" class="menu">
			<?php 
			//	print_r(json_decode($data,true));
				//Decode ClassList
			$classList = json_decode($data,true);
//print_r($classList);
			if(count($argv) > 1){
			    $tmpList = array();
			    $sel = null;
			    foreach($classList as $li){
				if($li['tag'][0] == $argv[1]){
				    $sel = $li;
				    break;
				}
			    }
			    print_r($sel);echo 'xx';
			}
				
			?>
			
			<?php foreach($classList as $li){ ?>
				<?php if(strlen($li['cn']) != 2)continue; ?>
				<a href="./class/<?=$li['tag'][0]?>"><li>
					<span style="margin-left:auto;"><?=$li['tag'][0]?></span>
					<ul>
					<?php for($i=1;$i < count($li['tag']);++$i) { ?>
					    <li class="info"><?=$li['tag'][$i]?></li>
					<?php }?>
					</ul>
				</li></a>
			<?php } ?>
		</ol>
		<ol id="boardMenu" class="menu">
			<?php $boardList = array() ; ?>
			<?php foreach($boardList as $li){?>
				<a>
				<li>
					<span style="margin-left:auto;"><?=$li['title']?></span>
				</li>
				</a>
			<?php } ?>	
		</ol>
	</body>

</html>

