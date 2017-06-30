<?php require_once('shared.php');
     
class vw_nav_menu
{
   function __construct() {
		
   }


   private function build_menu($menu,$lvl=0,$idx=0,$idx1=0,$idx2=0,$idx3=0)
   {
      $tmp_txt ='';
      if(!empty($menu)){
           $tmp_txt .= $lvl==0 ? '<ul id="navmenu">' : 
           ( ($lvl==1 ? '<span class="darrow">&#9660;</span>' : '<span class="rarrow">&#9654;</span>') .'<ul class="sub'.$lvl.'">');
              
           foreach ($menu as $row) {
                            
              if(isset($row['submenu'])){
                  $tmp_txt .='<li><a href="javascript:void(0);">'.$row['menu'].'</a>';  
                  if(!empty($row['submenu'])){
                    $tmp_txt .= $this->build_menu($row['submenu'],$lvl+1,$idx,$idx1,$idx2,$idx3); 
                    switch($lvl)
                    {
                      case 0 : $idx++;break;
                      case 1 : $idx1++;break;
                      case 2 : $idx2++;break;
                    } 
                  }  
              }else {
                $tmp_txt .='<li><a href="javascript:void(0);" onclick="menu(this,'.$lvl.','.$idx.','.$idx1.','.$idx2.','.$idx3.')" >'.$row['menu'].'</a>';  
                switch($lvl)
                {
                   case 1 : $idx1++;break;
                   case 2 : $idx2++;break;
                   case 3 : $idx3++;break;
                } 

              }
              $tmp_txt.='</li>';
           } 

           $tmp_txt .= '</ul>';
      }       
      return $tmp_txt;
   }

   function display(){
   	 
   	 
       $html_txt = '<h1>Navigation Menu</h1>';
       
       $arr_menu = array(array('menu'=>'hyperlink 1','link'=>'#'),
                         array('menu'=>'hyperlink 2','link'=>'#',
                                'submenu'=>array(array('menu'=>'hyperlink 2.1','link'=>'#'),
                                                 array('menu'=>'hyperlink 2.2','link'=>'#'),
                                                 array('menu'=>'hyperlink 2.3','link'=>'#')
                                                 )
                              ),
                         array('menu'=>'hyperlink 3','link'=>'#'),
                         array('menu'=>'hyperlink 4','link'=>'#',
                                'submenu'=>array(array('menu'=>'hyperlink 4.1','link'=>'#'),
                                                 array('menu'=>'hyperlink 4.2','link'=>'#'),
                                                 array('menu'=>'hyperlink 4.3','link'=>'#',
                                                        'submenu'=>array(array('menu'=>'hyperlink 4.3.1','link'=>'#'),
                                                                         array('menu'=>'hyperlink 4.3.2','link'=>'#'),
                                                                         array('menu'=>'hyperlink 4.3.3','link'=>'#')
                                                                         )
                                                      )
                                                 )
                              ),
                         array('menu'=>'hyperlink 5','link'=>'#')
                         );

       $dt = new dt_menu;
       $arr_menu = $dt->baca_menu();

       if(!empty($arr_menu)){          
         $html_txt .= $this->build_menu($arr_menu,0);
       }                    
          
   	 return $html_txt; 
   }
 
 }

 ?>