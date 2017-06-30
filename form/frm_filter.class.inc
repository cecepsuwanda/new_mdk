<?php require_once('shared.php');
     
class frm_filter
{
   
   function __construct() {
	
   }

   public function indikator($data)
   {
   	 $dt_tb=array();     
     $i=1;
	 if(!empty($data)){  	 
	   	 foreach($data as $row)
	   	 {
	        $dt_rw=array(array($i++,array()),
	        	         array(trim($row['nm_ind_ks']),array()),
	        	         array("<input type='radio' name='pra[$row[id_ind_ks]]' value='1'>",array('align'=>'center')),
	        	         array("<input type='radio' name='pra[$row[id_ind_ks]]' value='0'>",array('align'=>'center')),
	        	         array("<input type='radio' name='ks[$row[id_ind_ks]]' value='1'>",array('align'=>'center')),
	        	         array("<input type='radio' name='ks[$row[id_ind_ks]]' value='0'>",array('align'=>'center')),
	        	         array("<input type='radio' name='ks1[$row[id_ind_ks]]' value='1'>",array('align'=>'center')),
	        	         array("<input type='radio' name='ks1[$row[id_ind_ks]]' value='0'>",array('align'=>'center'))
	        	         );
	        
	        $dt_tb[]=$dt_rw;
	   	 }
     }

     $tb_filter = new mytable(array('id'=>'tbindikator','width'=>'100%'),
     	                      array(
     	                      	      array(array('No',array('rowspan'=>2)),
     	                      	      	    array('Indikator',array('rowspan'=>'2')),
     	                      	      	    array('Pra',array('colspan'=>'2')),
     	                      	      	    array('KS',array('colspan'=>'2')),
     	                      	      	    array('KS1',array('colspan'=>'2'))
     	                      	      	    ),
     	                      	       array(array('Terpenuhi',array()),
     	                      	      	    array('Tidak Terpenuhi',array()),
     	                      	      	    array('Terpenuhi',array()),
     	                      	      	    array('Tidak Terpenuhi',array()),
     	                      	      	    array('Terpenuhi',array()),
     	                      	      	    array('Tidak Terpenuhi',array())
     	                      	      	    ) 
     	                      	      ),
     	                      $dt_tb,
     	                      ''); 
    
     return $tb_filter->display();
   }

   public function cmb_filter($hide=array(),$show=array(),$okshow=array())
   {
      $unit = new dt_unit_detail;
      $mycmb=new mycmb;

      $html='<table>';
      $html.='<tr>';
      
      if(empty($hide) or (!isset($hide['kec'])) or  $hide['kec']){ 
       $html.='<td>'; 
       $html.="Kecamatan : <select id='kec'>".$mycmb->cmb_kec($unit->getkec())."</select>";     
       $html.=  ((!empty($okshow)) and (isset($okshow['kec'])) and (!$okshow['kec'])) ? '':'<input type="submit" value="Filter" id="filter_kec">';
       //$html.='<input type="submit" value="View" id="view_kec">';
       $html.='</td>';
      }
      if( empty($hide) or (!isset($hide['desa'])) or  $hide['desa']){
       $html.='<td>'; 
       $html.="Desa/Kelurahan : <select id='desa'>".$mycmb->cmb_desa()."</select>";     
       $html.= ((!empty($okshow)) and (isset($okshow['desa'])) and  (!$okshow['desa'])) ? '' : '<input type="submit" value="Filter" id="filter_desa">';
       //$html.='<input type="submit" value="View" id="view_desa">';
       $html.='</td>';
      }
      if( empty($hide) or (!isset($hide['dusun'])) or  $hide['dusun']){
       $html.='<td>'; 
       $html.="Dusun/RW : <select id='dusun'>".$mycmb->cmb_dusun()."</select>";     
       $html.= ((!empty($okshow)) and (isset($okshow['dusun'])) and  (!$okshow['dusun'])) ? '' : '<input type="submit" value="Filter" id="filter_dusun">';
       //$html.='<input type="submit" value="View" id="view_dusun">';
       $html.='</td>';
      }
      if( empty($hide) or (!isset($hide['rt'])) or  $hide['rt']){
        $html.='<td>'; 
        $html.="RT : <select id='rt'>".$mycmb->cmb_rt()."</select>";     
        $html.=((!empty($okshow)) and (isset($okshow['rt'])) and  (!$okshow['rt'])) ? '':'<input type="submit" value="Filter" id="filter_rt">';
        //$html.='<input type="submit" value="View" id="view_dusun">';
        $html.='</td>';
      }

      $html.='</tr>';
      $html.='</table>';

      if( !empty($show) and (isset($show['ks'])) and  $show['ks']){
         $html.='<br>'; 
         $html.='<input type="radio" name="cmbks" id="cmbks" value="pra_s"> PRA S ';
         $html.='<input type="radio" name="cmbks" id="cmbks" value="ks_1"> KS I ';
         $html.='<input type="radio" name="cmbks" id="cmbks" value="ks_2"> KS II ';
         $html.='<input type="radio" name="cmbks" id="cmbks" value="ks_3"> KS III ';
         $html.='<input type="radio" name="cmbks" id="cmbks" value="ks_3_p"> KS III+ ';
         $html.='<br>';
      } 

      if( !empty($show) and (isset($show['umur'])) and  $show['umur']){
         $html.='<br>'; 
         $html.=' <input type="radio" name="cmbumur" id="cmbumur" value="1" onclick="cmbclick(1)"> Umur = 
                  <input type="text" name="txtumur1" id="txtumur1" size="1%" onkeypress="return isNumberKey(event)" size="3" maxlength="3" disabled>';
         $html.=' <input type="radio" name="cmbumur" id="cmbumur" value="2" onclick="cmbclick(2)"> Umur < 
                  <input type="text"  name="txtumur2" id="txtumur2" size="1%" onkeypress="return isNumberKey(event)" size="3" maxlength="3" disabled>';
         $html.=' <input type="radio" name="cmbumur" id="cmbumur" value="3" onclick="cmbclick(3)"> Umur > 
                  <input type="text"  name="txtumur3" id="txtumur3" size="1%" onkeypress="return isNumberKey(event)" size="3" maxlength="3" disabled>';
         $html.=' <input type="radio" name="cmbumur" id="cmbumur" value="4" onclick="cmbclick(4)"> Umur  
                  <input type="text"  name="txtumur4" id="txtumur4" size="1%" onkeypress="return isNumberKey(event)" size="3" maxlength="3" disabled> - 
                  <input type="text"  name="txtumur5" id="txtumur5" size="1%" onkeypress="return isNumberKey(event)" size="3" maxlength="3" disabled>';
         $html.='<br>';         
      } 

      if( !empty($show) and (isset($show['edu'])) and  $show['edu']){
         $html.='<br>'; 
         $tb = new tb_gen('dbo_edu_lvl');
         $data = $tb->getData("Kd_edu=3 OR Kd_edu=5 OR Kd_edu=7 OR Kd_edu=9");
         $i=0;
         foreach($data as $rc_edu){ 
           $html.=" <input id='id_edu$i' name='id_edu$i' type='checkbox' value='$rc_edu[Kd_edu]'> ".strtoupper($rc_edu['Nm_edu_ind']);
           $html.=" ";
             $i++;
           } 
         $html.='<br>';  
      }

      if( !empty($show) and (isset($show['kb'])) and  $show['kb']){
         $html.='<br>'; 
         $html.='<input type="radio" name="cmbkb" id="cmbkb" value="1"> KB ';
         $html.='<input type="radio" name="cmbkb" id="cmbkb" value="0"> NON KB ';      
         $html.='<br>';
       } 

       if( !empty($show) and (isset($show['kb1'])) and  $show['kb1']){
         $html.='<br>'; 
         $html.='<input type="radio" name="cmbkb1" id="cmbkb1" value="1"> KB ';
         $html.='<input type="radio" name="cmbkb1" id="cmbkb1" value="2"> NON KB '; 
         $html.='<input type="radio" name="cmbkb1" id="cmbkb1" value="3"> KB & NON KB ';     
         $html.='<br>';
       } 

       if( !empty($show) and (isset($show['ks1'])) and  $show['ks1']){
         $html.='<br>'; 
         $html.='<input type="radio" name="cmbks1" id="cmbks1" value="1"> UMUM ';
         $html.='<input type="radio" name="cmbks1" id="cmbks1" value="2"> PRA S & KS I ';      
         $html.='<br>';
       }

       if( !empty($show) and (isset($show['kerja'])) and  $show['kerja']){
         $html.='<br>STATUS KERJA :'; 
         $html.='<input type="radio" name="cmbkerja" id="cmbkerja" value="1"> BEKERJA ';
         $html.='<input type="radio" name="cmbkerja" id="cmbkerja" value="2"> TIDAK BEKERJA ';      
         $html.='<br>';
       }

       if( !empty($show) and (isset($show['sekolah'])) and  $show['sekolah']){
         $html.='<br>STATUS SEKOLAH :'; 
         $html.='<input type="radio" name="cmbsekolah" id="cmbsekolah" value="1"> SEKOLAH ';
         $html.='<input type="radio" name="cmbsekolah" id="cmbsekolah" value="2"> TIDAK SEKOLAH ';      
         $html.='<br>';
       } 

      return $html;
   }

    
    


}

?>   