<?php require_once('shared.php');
     
class vw_index
{
   function __construct() {
		
   }
    
   public function filter()
   {
   	 $dt = new dt_indikator_ks;
     $frmfilter = new frm_filter;
     $frm_filter_indikator = $frmfilter->indikator($dt->getindikator('id_ind_ks>=6 and id_ind_ks<=36'));     
     $html_txt = $frm_filter_indikator;
     $html_txt .='<fieldset><legend>Hasil Filter : </legend><div id="data"></div></fieldset>';
     //'.$this->hsl_filter().';
     return $html_txt;
   }
   
   
   public function hsl_filter($pra=array(),$ks=array(),$ks1=array(),$subjudul,$idx=0,$kd='',$kd1='')
   {
      $dt_un = new dt_unit_detail;
      $dt_stat = new dt_stat;
      $dt_poll = new dt_poll;
      //echo 'Baca Kecamatan Dari Database<br>'; 
      switch($idx)
      {
        case 1 :  
                  if($kd==''){  
                    $data = $dt_un->getKec();
                    $dtjmlkk = $dt_stat->getStatKab();
                    $nama = 'Kecamatan';
                    $poll_where = "Kd_dist='1017'";
                    $poll_group = "kd_subdist";
                  }else{
                    $data = $dt_un->getdesa($kd);
                    $dtjmlkk = $dt_stat->getStatperKec($kd);
                    $nama = 'Desa';
                    $poll_where = "Kd_subdist='$kd'";
                    $poll_group = "kd_vill";  
                  }  
                  break;
        case 3 :  
                  if($kd==''){  
                    $data = $dt_un->getdesa($kd1);
                    $dtjmlkk = $dt_stat->getStatperKec($kd1);
                    $nama = 'Desa';
                    $poll_where = "Kd_subdist='$kd1'";
                    $poll_group = "kd_vill";
                  }else{
                     $data = $dt_un->getdusun($kd);
                     $dtjmlkk = $dt_stat->getStatperDesa($kd);
                     $nama = 'Dusun';
                     $poll_where = "Kd_vill='$kd'";
                     $poll_group = "kd_subvill";
                   }
                  break;
        case 5 :  
                   if($kd==''){  
                    $data = $dt_un->getdusun($kd1);
                    $dtjmlkk = $dt_stat->getStatperDesa($kd1);
                    $nama = 'Dusun';
                    $poll_where = "Kd_vill='$kd1'";
                    $poll_group = "kd_subvill";
                  }else{
                     $data = $dt_un->getRT($kd);
                     $dtjmlkk = $dt_stat->getStatperDusun($kd);
                     $nama = 'RT';
                     $poll_where = "Kd_subvill='$kd'";
                     $poll_group = "kd_neigh";
                   }
                  break;
      
      }
      
          
	  if(!empty($data) ){           
            
            $dt_stat=array();
            if(!empty($pra) and !empty($ks) and !empty($ks1))
            {
              $dt_stat = $dt_poll->getdatapoll($pra,$ks,$ks1,$poll_select,$poll_where,$poll_group);
            }

               
            $ttjmlkk = 0;
                  $ttjmljiwa = 0;
                  $ttjmlpra = 0;
                  $ttjmlks=0;
                  $ttjmlks1=0;
                  $ttjmlnon = 0;


            $arr_jml=array();
            if(!empty($dtjmlkk)){
              foreach($dtjmlkk as $row)
                  {                     
                     $arr_jml[$row['kode']]['jmlkk']=$row['jmlkk'];
                     $ttjmlkk = $ttjmlkk + $row['jmlkk'];
                     $arr_jml[$row['kode']]['jmljiwa']=$row['jmljiwa'];
                     $ttjmljiwa = $ttjmljiwa + $row['jmljiwa'];
                     $arr_jml[$row['kode']]['jmlpra']=isset($dt_stat[$row['kode']]['jmlpra']) ? $dt_stat[$row['kode']]['jmlpra'] : 0;
                     $ttjmlpra = $ttjmlpra + (isset($dt_stat[$row['kode']]['jmlpra']) ? $dt_stat[$row['kode']]['jmlpra'] : 0);
                     $arr_jml[$row['kode']]['jmlks']=isset($dt_stat[$row['kode']]['jmlks']) ? $dt_stat[$row['kode']]['jmlks'] : 0;
                     $ttjmlks = $ttjmlks + (isset($dt_stat[$row['kode']]['jmlks']) ? $dt_stat[$row['kode']]['jmlks'] : 0);
                     $arr_jml[$row['kode']]['jmlks1']=isset($dt_stat[$row['kode']]['jmlks1']) ? $dt_stat[$row['kode']]['jmlks1'] : 0;
                     $ttjmlks1 = $ttjmlks1 + (isset($dt_stat[$row['kode']]['jmlks1']) ? $dt_stat[$row['kode']]['jmlks1'] : 0);
                     $arr_jml[$row['kode']]['jmlnon']= (($row['jmlkk']>$dt_stat[$row['kode']]['jmlttl']) ? ($row['jmlkk']-$dt_stat[$row['kode']]['jmlttl']) : 0) ;   
                     $ttjmlnon = $ttjmlnon + (($row['jmlkk']>$dt_stat[$row['kode']]['jmlttl']) ? ($row['jmlkk']-$dt_stat[$row['kode']]['jmlttl']) : 0) ;
                     $arr_jml[$row['kode']]['jmlttl']=$dt_stat[$row['kode']]['jmlpra']+$dt_stat[$row['kode']]['jmlks']+$dt_stat[$row['kode']]['jmlks1']+($row['jmlkk']-$dt_stat[$row['kode']]['jmlttl']);  
                  }
               
            } 
            
            //print_r($dtjmlkk);
            
       //echo 'Tampilkan Data Statistik Per Kecamatan<br>';
        $i=1;
	   	 foreach($data as $row)
	   	 {	         
            
	        $dt_rw=array(array($i++,array()),
	        	         array(trim($row['no_unit_detail']),array()),
	        	         array(number_format($arr_jml[$row['id_unit_detail']]['jmlkk'],0,',','.'),array('align'=>'right')),
	        	         array(number_format($arr_jml[$row['id_unit_detail']]['jmljiwa'],0,',','.'),array('align'=>'right')),
	        	         array(number_format($arr_jml[$row['id_unit_detail']]['jmlpra'],0,',','.'),array('align'=>'right')),
	        	         array(number_format($arr_jml[$row['id_unit_detail']]['jmlks'],0,',','.'),array('align'=>'right')),
	        	         array(number_format($arr_jml[$row['id_unit_detail']]['jmlks1'],0,',','.'),array('align'=>'right')),
                     array(number_format($arr_jml[$row['id_unit_detail']]['jmlnon'],0,',','.'),array('align'=>'right')),                     
                     array(number_format($arr_jml[$row['id_unit_detail']]['jmlttl'],0,',','.'),array('align'=>'right')));
	        
	        $dt_tb[]=$dt_rw;
	   	 }
      }
      
      $txt = '';
            $txt = $txt."<tr>";
            $txt = $txt."<th colspan='2'>Jumlah</th>";                      
            $txt = $txt."<th align='right'>".number_format($ttjmlkk, 0, ',', '.')."</th>";
            $txt = $txt."<th align='right'>".number_format($ttjmljiwa, 0, ',', '.')."</th>";
            $txt = $txt."<th align='right'>".number_format($ttjmlpra, 0, ',', '.')."</th>";
            $txt = $txt."<th align='right'>".number_format($ttjmlks, 0, ',', '.')."</th>";
            $txt = $txt."<th align='right'>".number_format($ttjmlks1, 0, ',', '.')."</th>";
            $txt = $txt."<th align='right'>".number_format($ttjmlnon, 0, ',', '.')."</th>";
            $txt = $txt."<th align='right'></th>";                       
          $txt = $txt."</tr>";
           

      $tb_hslfilter = new mytable(array('id'=>'tbhslfilter','width'=>'100%'),
                                   array(array(array('No',array('rowspan'=>'2')),array("$nama",array('rowspan'=>'2')),array('Jumlah KK',array('rowspan'=>'2')),array('Jumlah Jiwa',array('rowspan'=>'2')),array('Tingkat Kesejahteraan Keluarga',array('colspan'=>'5'))),
                                         array('Pra','Sejahtera','Sejahtera 1','Non Klasifikasi','Total')),$dt_tb,$txt); 
     $html_txt .= "<center><bold>REKAPITULASI PER TINGKAT KESEJAHTERAAN KELUARGA<br>KABUPATEN BANDUNG BARAT</bold><br>$subjudul</center>".$tb_hslfilter->display();
     return $html_txt;  
   }


}


?>