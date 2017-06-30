
SELECT
  a.Kd_prop,
  a.Kd_dist,
  a.Kd_subdist,
  a.kd_vill,
  a.kd_subvill,
  a.kd_neigh,
  SUM((b.Kd_fammbrtyp = 1)) AS jmlkk,
  COUNT(*) AS jmljiwa
FROM (dbo_family a
   JOIN dbo_individu b
     ON ((a.Kd_fam = b.Kd_fam)))
GROUP BY a.Kd_prop,a.Kd_dist,a.Kd_subdist,a.kd_vill,a.kd_subvill,a.kd_neigh
ORDER BY a.Kd_prop,a.Kd_dist,a.Kd_subdist,a.kd_vill,a.kd_subvill,a.kd_neigh;

SELECT kd_fam,
  GROUP_CONCAT(IF((kd_prospinstat = 1),id_ind_ks,NULL) SEPARATOR ',') AS kond1,
  GROUP_CONCAT(IF((kd_prospinstat > 1),id_ind_ks,NULL) SEPARATOR ',') AS kond0
FROM dbo_fam_ind_detail
GROUP BY Kd_fam
ORDER BY id_ind_ks;

SELECT a.kd_fam,a.kd_prosplvl,b.id_ind_ks,b.kd_prospinstat,c.nm_ind_ks FROM (dbo_family a INNER JOIN  dbo_fam_ind_detail b ON a.kd_fam=b.kd_fam) INNER JOIN dbo_indikator_ks c ON b.id_ind_ks=c.id_ind_ks  
ORDER BY b.kd_fam ;