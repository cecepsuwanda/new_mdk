    
    var oTable;
    
   

    function bind_indks(data)
    {
       
       oTable=$("#tbindikator").dataTable({"bAutoWidth":false});

        $("#simpan_ind_ks").click(function () {
            dt_table = 'action=menu&issave=1&menu_lvl='+menu_lvl+'&menu_idx='+menu_idx+'&menu_idx1='+menu_idx1+'&menu_idx2='+menu_idx2+'&menu_idx3='+menu_idx3+
           '&'+$(":input",oTable.fnGetNodes()).serialize();
           myajax_cmb('indikator',dt_table,function(){
             $('#indikator').html("<font size='5' color='red'>Silahkan Tunggu, Sedang Proses ....<\/font> <img src='img/ajax-loader.gif' />");
   
           },function(data){
             oTable=$("#tbindikator").dataTable({"bAutoWidth":false}); 
           });              
        });

        $("#clear_ind_ks").click(function () {
            data = 'action=menu&isclear=1&menu_lvl='+menu_lvl+'&menu_idx='+menu_idx+'&menu_idx1='+menu_idx1+'&menu_idx2='+menu_idx2+'&menu_idx3='+menu_idx3;
            myajax_cmb('indikator',data,function(){
             $('#indikator').html("<font size='5' color='red'>Silahkan Tunggu, Sedang Proses ....<\/font> <img src='img/ajax-loader.gif' />");
   
           },function(data){
             oTable=$("#tbindikator").dataTable({"bAutoWidth":false}); 
           });              
        });
    }

    

    function myajax_cmb(id,data,fbefore=null,fafter=null) {
        
        if(fbefore != null){
            if(typeof fbefore==='function'){
               fbefore();
            }
        }
        
        $.ajax({
            "type" : "post",
            "url" : "change_content.php",
            "cache" : false,
            "data" : data,
            success : function (data) {
                if(id!=''){
                  $('#'+id).html(data);
                }
                
                if(fafter != null){
                    if(typeof fafter==='function'){
                       fafter(data);
                    }
                }
            }
        });
     }

      function myajax_filter(data1) {
        $('#data').html("<font size='5' color='red'>Silahkan Tunggu, Sedang Proses ....<\/font> <img src='img/ajax-loader.gif' />");

        $.ajax({
            "type" : "post",
            "url" : "change_content.php",
            "cache" : false,
            "data" : data1,
            success : function (data) {
                $('#data').html(data);                
                $("#tbhslfilter").dataTable({"bAutoWidth":false});                 
                
			
			var aoColumnDefs = [{'sClass' : 'center','aTargets':[0]}];
			
			if((menu_idx==3 && menu_idx1==0))
			{
				aoColumnDefs = [{'sClass' : 'center','aTargets':[0,2]}];
			}
			    			
			if(menu_idx==1)
                {
                  if (menu_idx1==0 || menu_idx1==1)
                  {					  
				   bind_cmb(null);
				  }else{
					  if(menu_idx1==3)
					  {
						  aoColumnDefs = [{'sClass' : 'center','aTargets':[0,1,2]}];
					  }
				  } 
                }	
				
				
			oTable=$("#tbserverside").dataTable({
                    'bProcessing': true,
                    'bServerSide': true,
                    'sAjaxSource': 'change_content.php',
                    'sServerMethod' : 'POST',
                   	'aoColumnDefs': aoColumnDefs,
					'fnServerParams' : function(aoData){
                        var idkec = data1.match(/idkec=([0-9]*)/g)
                           if(idkec!=null){
                              idkec=idkec[0].split('=')[1];
                           }
                        var iddesa = data1.match(/iddesa=([0-9]*)/g);
                           if(iddesa!=null){
                              iddesa=iddesa[0].split('=')[1];
                           }
                        var iddusun = data1.match(/iddusun=([0-9]*)/g);
                           if(iddusun!=null){
                              iddusun=iddusun[0].split('=')[1];
                           }
                        var idrt = data1.match(/idrt=([0-9]*)/g);
                           if(idrt!=null){
                              idrt=idrt[0].split('=')[1];
                           }
                        aoData.push({"name":"action","value":"menu"},
                                    {"name":"ispaging","value":"1"},
                                    {"name":"menu_lvl","value":menu_lvl},
                                    {"name":"menu_idx","value":menu_idx},
                                    {"name":"menu_idx1","value":menu_idx1},
                                    {"name":"menu_idx2","value":menu_idx2},
                                    {"name":"menu_idx3","value":menu_idx3},
                                    {"name":"data","value":data1},
                                    {"name":"idkec","value":idkec},
                                    {"name":"iddesa","value":iddesa},
                                    {"name":"iddusun","value":iddusun},
                                    {"name":"idrt","value":idrt}
                                    );
                    } 
                });

                $("#tabhslfilter").tabs();
                //$("table.display").dataTable({"bAutoWidth":false});
                

                //$("#treetable").treetable({ expandable: true });
                
            },
            error : function (jqXHR, textStatus, errorThrown) {

                var txt = textStatus;
                if (jqXHR.responseText) {
                    var r = jQuery.parseJSON(jqXHR.responseText);
                    txt = "Message: " + r.Message + "<br>StackTrace: " + r.StackTrace + "<br>ExceptionType: " + r.ExceptionType;
                }
                $("#data").html(txt);
            }

        });
     }