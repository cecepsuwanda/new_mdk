<?php require_once('shared.php');
     
class dt_family
{
   private $tb_;
   
   function __construct() {
	$this->tb_ = new tb_gen('dbo_family');
   }

   function getdata($where)
   {
     $data = $this->tb_->getData($where);
     return $data;
   }

   public function getstat($select,$from,$where,$groupby)
   {
    
    $tb_stat = new tb_gen('tbgen');
    //$dt=$tb_stat->getDataStrdProc("get_stat('$select','$from',".'"'.$where.'"'.",'$groupby')");
    $tb_stat->sql_select = $select;
    $tb_stat->sql_from = $from;
    $tb_stat->sql_groupby = $groupby;
    $dt =  $tb_stat->getData($where);
     return $dt;
   }
   
   public function getkki($iddesa)
   {
     $this->tb_->sql_select = 'Kd_unik_fam';
     $this->tb_->sql_orderby = 'Kd_unik_fam desc'; 
     $data = $this->tb_->getData("kd_vill='$iddesa'");  

     $tmp_kki = '0000001';
     if(!empty($data))
     {
       $tmp_kki = str_pad(intval($data[0]['Kd_unik_fam'])+1,7,'0',STR_PAD_LEFT);
     }
     return trim($tmp_kki);

   }

   public function kki_exist($kki)
   {
     $data = $this->tb_->getData("Kd_fam='$kki'");
     return empty($data) ? 0 : 1;
   }

   /*public function reset_prosplvl($where)
   {
      $tb_stat = new tb_gen('tbgen');
      $tb_stat->execStrdProc("reset_prosplvl('$where')");
   }

   public function set_prosplvl($idx,$select,$from,$where)
   {
    
    $tb_stat = new tb_gen('tbgen');
    $tb_stat->execStrdProc("set_prosplvl($idx,'$select','$from',".'"'.$where.'"'.")");
     
   }*/

   function update_kdprosplvl($kd_prosplvl,$where)
   {
     $this->tb_->create("UPDATE (dbo_family a INNER JOIN (SELECT kd_fam 
                                                        FROM vw_fam_ind_detail  
                                                        WHERE $where) b ON a.kd_fam=b.kd_fam)
                        SET a.kd_prosplvl=$kd_prosplvl where a.Kd_prosplvl=0 and a.Kd_dist='1017'");
   }

   public function updatedata($field,$where)
   {
   	  $this->tb_->updateAllRecord($field,$where);   	  
   }

   public function updatedata1($fieldarray)
   {
      $this->tb_->updateRecord($fieldarray);       
   }

   function insert_data($data)
   {
     $this->tb_->insertRecord($data);
   }

   function delete_data($data)
   {
     $this->tb_->deleteRecord($data); 
   }

}

?>   