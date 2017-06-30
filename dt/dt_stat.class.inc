<?php require_once('shared.php');
     
class dt_stat
{

   private $tb_;
   
   function __construct() {
	 
	 $tb = new tb_gen('tbgen');     
     $isviewexist = $tb->isviewexist('vw_stat');
     if(!$isviewexist)
     {
       $tb->createview('vw_stat','SELECT a.Kd_prop,  a.Kd_dist,  a.Kd_subdist,  a.kd_vill,  a.kd_subvill,  a.kd_neigh,  SUM((b.Kd_fammbrtyp = 1)) AS jmlkk,  COUNT(*) AS jmljiwa FROM (dbo_family a JOIN dbo_individu b ON ((a.Kd_fam = b.Kd_fam))) GROUP BY a.Kd_prop,a.Kd_dist,a.Kd_subdist,a.kd_vill,a.kd_subvill,a.kd_neigh ORDER BY a.Kd_prop,a.Kd_dist,a.Kd_subdist,a.kd_vill,a.kd_subvill,a.kd_neigh');
     }


	 $this->tb_ = new tb_gen('vw_stat');
   }

   public function getStatKab()
   {
     $this->tb_->sql_select = 'Kd_prop,Kd_dist,Kd_subdist as kode,SUM(jmlkk) AS jmlkk,sum(jmljiwa) AS jmljiwa';
     $this->tb_->sql_groupby = 'Kd_prop,Kd_dist,Kd_subdist';
     $this->tb_->sql_orderby = 'Kd_prop,Kd_dist,Kd_subdist';
     $data= $this->tb_->getdata("kd_dist='1017'");
     return $data;
   }

   public function getStatperKec($kd)
   {
     $this->tb_->sql_select = 'Kd_prop,Kd_dist,Kd_subdist,kd_vill as kode,SUM(jmlkk) AS jmlkk,sum(jmljiwa) AS jmljiwa';
     $this->tb_->sql_groupby = 'Kd_prop,Kd_dist,Kd_subdist,kd_vill';
     $this->tb_->sql_orderby = 'Kd_prop,Kd_dist,Kd_subdist,kd_vill';
     $data= $this->tb_->getdata("Kd_subdist='$kd'");
     return $data;
   }

   public function getStatperDesa($kd)
   {
     $this->tb_->sql_select = 'Kd_prop,Kd_dist,Kd_subdist,kd_vill,kd_subvill as kode,SUM(jmlkk) AS jmlkk,sum(jmljiwa) AS jmljiwa';
     $this->tb_->sql_groupby = 'Kd_prop,Kd_dist,Kd_subdist,kd_vill,kd_subvill';
     $this->tb_->sql_orderby = 'Kd_prop,Kd_dist,Kd_subdist,kd_vill,kd_subvill';
     $data= $this->tb_->getdata("kd_vill='$kd'");
     return $data;
   } 

   public function getStatperDusun($kd)
   {
     $this->tb_->sql_select = 'Kd_prop,Kd_dist,Kd_subdist,kd_vill,kd_subvill,kd_neigh as kode,jmlkk,jmljiwa';
     $this->tb_->sql_orderby = 'Kd_prop,Kd_dist,Kd_subdist,kd_vill,kd_subvill,kd_neigh';
     $data= $this->tb_->getdata("kd_subvill='$kd'");
     return $data;
   }     

}