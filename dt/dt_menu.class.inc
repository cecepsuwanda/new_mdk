<?php require_once('shared.php');
     
class dt_menu
{
	function __construct() {

	}

	function baca_menu()
	{
		$tmp_menu = array();
        
        $tb = new tb_gen('dbo_menu');
        $tb->sql_orderby='no_urut_menu';
        $data = $tb->getData('id_induk_menu IS NULL');

        if(!empty($data))
        {
           foreach($data as $row)
           {
           	   $tmp = array('menu'=>$row['nm_menu'],
           	   	                   'link'=>(($row['link_menu']=='' or $row['link_menu']==null) ? '#' : $row['link_menu'])
           	   	                   );
               
               $data1 = $tb->getData('id_induk_menu = '.$row['id_menu']);
               if(!empty($data1))
               {
               	 $tmp1=array();
               	 foreach($data1 as $row1)
               	 {
                   $tmp_tmp1 = array('menu'=>$row1['nm_menu'],
           	   	                   'link'=>(($row1['link_menu']=='' or $row1['link_menu']==null) ? '#' : $row1['link_menu'])
           	   	                   ); 
                   $data2 = $tb->getData('id_induk_menu = '.$row1['id_menu']);
                   if(!empty($data2))
                   { 
                      $tmp2=array();
                      foreach($data2 as $row2)
               	      {
                        $tmp_tmp2 = array('menu'=>$row2['nm_menu'],
           	   	                   'link'=>(($row2['link_menu']=='' or $row2['link_menu']==null) ? '#' : $row2['link_menu'])
           	   	                   ); 
                        $data3 = $tb->getData('id_induk_menu = '.$row2['id_menu']);
                        if(!empty($data3))
                        {
                           $tmp3=array();
                           foreach($data3 as $row3)
               	           {
                              $tmp3[] = array('menu'=>$row3['nm_menu'],
           	   	                   'link'=>(($row3['link_menu']=='' or $row3['link_menu']==null) ? '#' : $row3['link_menu'])
           	   	                   ); 
               	           }
               	           $tmp_tmp2['submenu']=$tmp3;	
                        }
                        $tmp2[] = $tmp_tmp2; 
               	      } 
               	      $tmp_tmp1['submenu'] = $tmp2;
                   } 
                   $tmp1[] = $tmp_tmp1; 	 	
               	 }
                  $tmp['submenu']=$tmp1;
               }   

               
           	   $tmp_menu[] =  $tmp;
           }
        }

		return $tmp_menu;
	}

}

?>