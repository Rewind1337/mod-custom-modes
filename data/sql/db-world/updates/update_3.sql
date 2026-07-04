DROP TABLE IF EXISTS `hardmode_modes`;
CREATE TABLE IF NOT EXISTS `hardmode_modes` (
  `id` tinyint unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL,
  `description` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci DEFAULT NULL,
  `restrictions` bigint unsigned DEFAULT NULL,
  `enabled` tinyint DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;


UPDATE gameobject_template SET ScriptName = "HardModeShrineObject" WHERE entry = 441101;

DROP TABLE IF EXISTS `hardmode_auras`;
CREATE TABLE IF NOT EXISTS `hardmode_auras` (
  `mode` int NOT NULL,
  `aura` int NOT NULL,
  `description` varchar(50) COLLATE utf8mb4_general_ci DEFAULT NULL,
  PRIMARY KEY (`mode`,`aura`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;