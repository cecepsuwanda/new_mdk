        $('#navmenu li').hover(function(){
            var container = $(this),
                list = container.find(".sub1 > li > a"),maxlength=0;
            
            list.each(function(index){              
              if(maxlength<$(this).text().length){  
               maxlength = $(this).text().length;
              }               
            });    
            
           if(maxlength>40)
           {
              container.find(".sub1 > li").show().css({width:'230px'});
              container.find(".sub1 > li a").show().css({width:'230px'});
           }

        });

        $('.sub1 li').hover(function(){
            var container = $(this),
                list = container.find(".sub2 > li > a"),maxlength=0;
            
            list.each(function(index){              
               if(maxlength<$(this).text().length){  
                  maxlength = $(this).text().length;
                }               
            });    
            
            if(maxlength>40)
           {
              container.find(".sub2 > li").show().css({width:'230px'});
              container.find(".sub2 > li a").show().css({width:'230px'});
           }

            if(maxlength>100)
           {
              container.find(".sub2 > li").show().css({width:'680px'});
              container.find(".sub2 > li a").show().css({width:'680px'});
           } 
        });

        $('.sub2 li').hover(function(){
            var container = $(this),
                list = container.find(".sub3 > li > a"),maxlength=0;
            
            list.each(function(index){              
               if(maxlength<$(this).text().length){  
               maxlength = $(this).text().length;
              }               
            });    
            if(maxlength>80)
           {              
              container.find(".sub3 > li").show().css({width:'460px'});
              container.find(".sub3 > li a").show().css({width:'460px'});              
           }
        });


        function menu(menu_data,lvl,idx,idx1,idx2,idx3)
        {
          
          menu_lvl=lvl;
          menu_idx=idx;
          menu_idx1=idx1;
          menu_idx2=idx2;
          menu_idx3=idx3;


          var sub1=$(".sub1 > li:contains('"+menu_data.text+"') > a"),
              sub2=$(".sub2 > li:contains('"+menu_data.text+"') > a"),
              sub3=$(".sub3 > li:contains('"+menu_data.text+"') > a"),
              main=$("ul#navmenu > li:contains('"+menu_data.text+"') > a"),
              nm_menu='',i=0,ctk=1;
          
          
          main.each(function(nm){               
               nm_menu += $(this).text();
          });  

          sub1.each(function(nm){              
               nm_menu += ' > ';
               nm_menu += $(this).text();
          });

                        
            sub2.each(function(nm){              
              
              if(sub2.size()>1){
                
                if(nm==idx2){
                   ctk=1;
                 }else{
                   ctk=0;
                 }
              }else{
                ctk=1;
              }

              if(ctk==1){
                nm_menu += ' > ';
                nm_menu += $(this).text();
              }  
            });
          
            
          
               
            sub3.each(function(nm){               
                if(i==0){ 
                  nm_menu += ' > ';
                  nm_menu += $(this).text();
                  i++;
                }                 
            });
                      
          menu_txt = nm_menu;

          var data = 'action=menu&nm_menu='+nm_menu+'&menu_lvl='+lvl+'&menu_idx='+idx+
                                                                     '&menu_idx1='+idx1+
                                                                     '&menu_idx2='+idx2+
                                                                     '&menu_idx3='+idx3;


          
          switch(idx)
          {
            case 0 : myajax_cmb('content',data,null,function(){
              $("#tbtypeuser").dataTable({"bAutoWidth":false});
            });
                   break; 
            default : myajax_cmb('content',data,null,bind_cmb);
                     break; 
                      
          } 
        }