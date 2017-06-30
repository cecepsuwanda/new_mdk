<?php require_once('shared.php');
     
class dt_setup
{
   private $dt_kat;
   private $dt_fam;  
   function __construct() {

		  $tb = new tb_gen('tbgen');     
      $isviewexist = $tb->isviewexist('vw_fam_ind_detail');
      if(!$isviewexist)
      {
        $tb->createview('vw_fam_ind_detail',"SELECT kd_fam,GROUP_CONCAT(IF(kd_prospinstat=1,id_ind_ks,'*')) AS N1, GROUP_CONCAT(IF(kd_prospinstat>1,id_ind_ks,'*')) AS N0 FROM dbo_fam_ind_detail GROUP BY kd_fam ORDER BY id_ind_ks");
      }

      $this->dt_kat = new dt_kategori;
      $this->dt_fam = new dt_family;

   }

   function save_ind_ks($id_pra_s,$id_ks_1,$id_ks_2,$id_ks_3,$id_ks_3_p)
   {
           
      $str_pra_ks=$this->dt_kat->build_wherestr($id_pra_s);
      $this->dt_kat->save_kategori($id_pra_s,1);
      
      $str_ks_1=$this->dt_kat->build_wherestr($id_ks_1);
      $this->dt_kat->save_kategori($id_ks_1,2);
        
      $str_ks_2=$this->dt_kat->build_wherestr($id_ks_2);
      $this->dt_kat->save_kategori($id_ks_2,3);

      $str_ks_3=$this->dt_kat->build_wherestr($id_ks_3);
      $this->dt_kat->save_kategori($id_ks_3,4);

      $str_ks_3_p=$this->dt_kat->build_wherestr($id_ks_3_p);
      $this->dt_kat->save_kategori($id_ks_3_p,5);

      set_time_limit(0);
      $this->dt_fam->updatedata('Kd_prosplvl=0','Kd_prosplvl>0 and kd_dist="1017"');

      $this->dt_fam->update_kdprosplvl(5,$str_ks_3_p);
      $this->dt_fam->update_kdprosplvl(4,$str_ks_3);
      $this->dt_fam->update_kdprosplvl(3,$str_ks_2);
      $this->dt_fam->update_kdprosplvl(2,$str_ks_1);
      $this->dt_fam->update_kdprosplvl(1,$str_pra_ks);                                                           
     
   }

   function clear_ind_ks()
   {
           
      $tb_kat = new tb_gen('dbo_kategori');
      $dt_kat = $tb_kat->deleteAllRecord('id_kat>8');                                   
     
   }

   function getdtmenu02()
	{
      $tb_indks = new tb_gen('dbo_indikator_ks');
	    $tb_indks->sql_orderby='id_ind_ks';
	    $dt_indks = $tb_indks->getdata('id_ind_ks>5 and id_ind_ks<=36');

      $tb_prosplvl = new tb_gen('dbo_prosp_lvl');
      $tb_prosplvl->sql_orderby='no_urut';
	    $dt_prosplvl = $tb_prosplvl->getdata('Kd_prosplvl not in (6,7)');
      
      $dt_tb = array();
      $i=1;
      if(!empty($dt_indks))
      {
        foreach($dt_indks as $row)
        {
        	$tmp_dt_tb=array();
			    $tmp_dt_tb[]=$i;
			    $tmp_dt_tb[]=$row['nm_ind_ks'];
            
            foreach($dt_prosplvl as $row1)
            {
                $tmp = $this->dt_kat->getarrkat($row1['Kd_prosplvl'],$row['id_ind_ks']);              
                $checked1 = $tmp == 1 ? 'checked' : '';
                $checked0 = $tmp == 0 ? 'checked' : '';              

              $tmp_dt_tb[]="<input type='radio' name='id_".$row1['Kd_prosplvl']."[$row[id_ind_ks]]' value='1' $checked1 >";
              $tmp_dt_tb[]="<input type='radio' name='id_".$row1['Kd_prosplvl']."[$row[id_ind_ks]]' value='0' $checked0 >";
            
            }

			$dt_tb[] = $tmp_dt_tb;
			$i++; 
        }
      }

      return $dt_tb;
    }		

 }  


?>