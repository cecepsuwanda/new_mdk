<?php require_once('shared.php');
     
class vw_setup
{
   
   function __construct() {
		
   }

   

   private function build_dt_tb($tmp_dt_tb)
   {
       $dt_tb=array();
       $txt='';
       if(!empty($tmp_dt_tb))
       {
         
          foreach($tmp_dt_tb as $row)
          {
             $tmp=array();
            foreach ($row as $key => $value) {
               $tmp[]=array($value,array());            
            } 
             $dt_tb[]=$tmp;
          }
       return $dt_tb;
   }
  } 

   function save_ind_ks($id_pra_s,$id_ks_1,$id_ks_2,$id_ks_3,$id_ks_3_p)
   {
    $dt_setup = new dt_setup;
    $tmp=$dt_setup->save_ind_ks($id_pra_s,$id_ks_1,$id_ks_2,$id_ks_3,$id_ks_3_p);    
    return $this->baca_tbindikatorks();
   }

   function clear_ind_ks()
   {
    $dt_setup = new dt_setup;
    $tmp=$dt_setup->clear_ind_ks();
    
    return $this->baca_tbindikatorks();
   }

   private function baca_tbindikatorks()
   {
      $dt_setup = new dt_setup;
      $tmp_dt_tb = $dt_setup->getdtmenu02();
    
      $dt_tb = $this->build_dt_tb($tmp_dt_tb);

      $tb_hslfilter = new mytable(array('id'=>'tbindikator','width'=>'100%'),
                                   array(array(array('NO. KODE',array('rowspan'=>'3')),
                                               array("INDIKATOR",array('rowspan'=>'3')),
                                               array('TAHAPAN KELUARGA SEJAHTERA',array('colspan'=>'10')),
                                               ),
                                          array(array('PRA S',array('colspan'=>'2')), 
                                                array('KS I',array('colspan'=>'2')),
                                                array('KS II',array('colspan'=>'2')),
                                                array('KS III',array('colspan'=>'2')),
                                                array('KS III+',array('colspan'=>'2'))
                                                ),
                                          array(array('YES',array()), 
                                                array('NO',array()),
                                                array('YES',array()), 
                                                array('NO',array()),
                                                array('YES',array()), 
                                                array('NO',array()),
                                                array('YES',array()), 
                                                array('NO',array()),
                                                array('YES',array()), 
                                                array('NO',array())
                                                )
                                          ),
                                   $dt_tb,'');

       return $tb_hslfilter->display();
   }

   function menu02_hslfilter()
   {
   	  $html_txt = "<center><bold>INDIKATOR KELUARGA SEJAHTERA</bold><br><br></center>";
      $html_txt .= "<center><input type='submit' value='Simpan' id='simpan_ind_ks'><input type='submit' value='Clear' id='clear_ind_ks'></center>";
      $html_txt .= "<div id='indikator'>".$this->baca_tbindikatorks().'</div>';
      return $html_txt;
   }

   
   function menu04_view()
   {
      $html_txt ="<center><bold>TYPE USER, MENU AKSES DAN USER</bold><br><br></center>";


      $tb_typeuser = new mytable(array('id'=>'tbtypeuser','width'=>'100%'),
                                   array( array(array('TYPE USER',array()), 
                                                array('KETERANGAN',array()),
                                                array('UNIT',array()),
                                                array('ACTION',array()) 
                                                )
                                          ),
                                   '','');

      $html_txt .="<div id='divtypeuser'>".$tb_typeuser->display('')."</div>";

      return $html_txt;
   }

 } 


?>