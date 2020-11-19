drop DATABASE `mytest`;
CREATE DATABASE `mytest` /*!40100 DEFAULT CHARACTER SET utf8 */;
use mytest;
CREATE TABLE `test_info` (
`id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
`age` int(11) DEFAULT NULL,
`name` varchar(45) DEFAULT NULL,
`enable` tinyint(1) DEFAULT 1,
`created_at` datetime DEFAULT CURRENT_TIMESTAMP,
`last_date` datetime DEFAULT NULL,
PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
