<?PHP require_once('shared.php'); ?>

<html>

<head>
   <meta name="viewport" content="width=devie-width, initial-scale=1"> 
   <title>BKKBN</title>
   <style type="text/css">
/*<![CDATA[*/
                @import "datatables/media/css/demo_page.css";
                @import "datatables/media/css/demo_table.css";
                .ui-widget { font-family: Trebuchet MS, Tahoma, Verdana, Arial, sans-serif; font-size: 12px; }
                table#tbserverside { font-size: 9px; }
                table#tbhslfilter  { font-size: 9px; }
                table#tbindikator  { font-size: 9px; }
                table#tbjudul  { font-size: 9px; } 
                table.display { font-size: 9px; } 
                table.mystyle  { font-size: 9px; }  
                table#tbalamat { font-size: 9px; }
                table#tbindv { font-size: 9px; }
                table#tbstat { font-size: 9px; }


  /*]]>*/         

  </style>
    <link type="text/css" href="css/nav_bar.css" rel="stylesheet" />
    <link type="text/css" href="css/index.css" rel="stylesheet" />
    <link type="text/css" href="css/style.css" rel="stylesheet" />
    <link type="text/css" href="css/jquery-ui-1.8.23.custom.css" rel="stylesheet" />
    <link type="text/css" href="treetable/stylesheets/jquery.treetable.css" rel="stylesheet" />
    <!--<link rel="stylesheet" href="treetable/stylesheets/screen.css" media="screen" />-->
    <link rel="stylesheet" href="treetable/stylesheets/jquery.treetable.theme.default.css" />
    
    <script type="text/javascript" src="js/jquery-1.8.0.min.js"></script>
    <script type="text/javascript" src="js/jquery-ui-1.8.23.custom.min.js"></script>
    <script type="text/javascript" src="datatables/media/js/jquery.dataTables.js"></script>

    <script type="text/javascript" src="treetable/javascripts/src/jquery.treetable.js"></script>    

    
</head>

<body>
  
  <?php
    $menu= new vw_nav_menu;
    echo $menu->display();
  ?>
  
  <div id="content"> </div>
  
   <script type="text/javascript" src="js/index.js"></script>
   <script type="text/javascript" src="js/filter.js"></script>
   <script type="text/javascript" src="js/menu.js"></script>
   <script type="text/javascript" src="js/form_add.js"></script>
   
   <script type="text/javascript">    

     $(document).ready(function () {     	
     	$.ajaxSetup({
     		type : 'POST',
     		headers : {
     			"cache-control" : "no-cache"
     		}
     	});
      
     });
   </script>
 </body>
   
</html>
