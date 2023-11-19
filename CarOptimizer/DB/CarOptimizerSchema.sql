CREATE DATABASE  IF NOT EXISTS `caroptimizerschema` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `caroptimizerschema`;
-- MySQL dump 10.13  Distrib 8.0.34, for Win64 (x86_64)
--
-- Host: localhost    Database: caroptimizerschema
-- ------------------------------------------------------
-- Server version	8.0.34

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `car_configurations`
--

DROP TABLE IF EXISTS `car_configurations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `car_configurations` (
  `configuration_id` int NOT NULL AUTO_INCREMENT,
  `configuration_name` varchar(30) NOT NULL,
  `car_id` int NOT NULL,
  `user_id` int NOT NULL,
  PRIMARY KEY (`configuration_id`),
  KEY `car_id_PK` (`car_id`),
  KEY `user_id_FK` (`user_id`),
  CONSTRAINT `car_id_PK` FOREIGN KEY (`car_id`) REFERENCES `cars` (`car_id`),
  CONSTRAINT `user_id_FK` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `car_configurations`
--

LOCK TABLES `car_configurations` WRITE;
/*!40000 ALTER TABLE `car_configurations` DISABLE KEYS */;
/*!40000 ALTER TABLE `car_configurations` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cars`
--

DROP TABLE IF EXISTS `cars`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `cars` (
  `car_id` int NOT NULL AUTO_INCREMENT,
  `car_make` varchar(30) NOT NULL,
  `car_model` varchar(30) NOT NULL,
  `car_year` int NOT NULL,
  `torque` int NOT NULL,
  `horsepower` decimal(10,0) NOT NULL,
  `weight` decimal(10,0) NOT NULL,
  PRIMARY KEY (`car_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cars`
--

LOCK TABLES `cars` WRITE;
/*!40000 ALTER TABLE `cars` DISABLE KEYS */;
/*!40000 ALTER TABLE `cars` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customer_support`
--

DROP TABLE IF EXISTS `customer_support`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `customer_support` (
  `ticket_id` int NOT NULL AUTO_INCREMENT,
  `category` varchar(30) NOT NULL,
  `ticket_description` text NOT NULL,
  `feedback` text NOT NULL,
  `ticket_status` enum('Opened','Closed','In Progress','Resolved') NOT NULL,
  `user_id` int NOT NULL,
  PRIMARY KEY (`ticket_id`),
  KEY `user_id_cust_supp_FK` (`user_id`),
  CONSTRAINT `user_id_cust_supp_FK` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer_support`
--

LOCK TABLES `customer_support` WRITE;
/*!40000 ALTER TABLE `customer_support` DISABLE KEYS */;
/*!40000 ALTER TABLE `customer_support` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `manufacturers`
--

DROP TABLE IF EXISTS `manufacturers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `manufacturers` (
  `manufacturer_id` int NOT NULL AUTO_INCREMENT,
  `manufacturer_name` varchar(30) NOT NULL,
  `manufacturer_location` varchar(30) NOT NULL,
  `manufacturer_website` text NOT NULL,
  `manufacturer_description` text NOT NULL,
  PRIMARY KEY (`manufacturer_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `manufacturers`
--

LOCK TABLES `manufacturers` WRITE;
/*!40000 ALTER TABLE `manufacturers` DISABLE KEYS */;
/*!40000 ALTER TABLE `manufacturers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `parts`
--

DROP TABLE IF EXISTS `parts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `parts` (
  `part_id` int NOT NULL AUTO_INCREMENT,
  `part_name` varchar(25) NOT NULL,
  `part_description` text NOT NULL,
  `price` double(10,2) NOT NULL,
  `manufacturer_id` int NOT NULL,
  PRIMARY KEY (`part_id`),
  KEY `manufacturer_name_FK` (`manufacturer_id`),
  CONSTRAINT `manufacturer_name_FK` FOREIGN KEY (`manufacturer_id`) REFERENCES `manufacturers` (`manufacturer_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `parts`
--

LOCK TABLES `parts` WRITE;
/*!40000 ALTER TABLE `parts` DISABLE KEYS */;
/*!40000 ALTER TABLE `parts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `parts_in_configurations`
--

DROP TABLE IF EXISTS `parts_in_configurations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `parts_in_configurations` (
  `part_id` int NOT NULL,
  `configuration_id` int NOT NULL,
  PRIMARY KEY (`part_id`,`configuration_id`),
  KEY `configuration_id_FK` (`configuration_id`),
  CONSTRAINT `configuration_id_FK` FOREIGN KEY (`configuration_id`) REFERENCES `car_configurations` (`configuration_id`),
  CONSTRAINT `part_id_config_FK` FOREIGN KEY (`part_id`) REFERENCES `parts` (`part_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `parts_in_configurations`
--

LOCK TABLES `parts_in_configurations` WRITE;
/*!40000 ALTER TABLE `parts_in_configurations` DISABLE KEYS */;
/*!40000 ALTER TABLE `parts_in_configurations` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `parts_suppliers`
--

DROP TABLE IF EXISTS `parts_suppliers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `parts_suppliers` (
  `part_id` int NOT NULL,
  `supplier_id` int NOT NULL,
  PRIMARY KEY (`part_id`,`supplier_id`),
  KEY `supplier_id_FK` (`supplier_id`),
  CONSTRAINT `part_id_FK` FOREIGN KEY (`part_id`) REFERENCES `parts` (`part_id`),
  CONSTRAINT `supplier_id_FK` FOREIGN KEY (`supplier_id`) REFERENCES `suppliers` (`supplier_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `parts_suppliers`
--

LOCK TABLES `parts_suppliers` WRITE;
/*!40000 ALTER TABLE `parts_suppliers` DISABLE KEYS */;
/*!40000 ALTER TABLE `parts_suppliers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `reviews`
--

DROP TABLE IF EXISTS `reviews`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `reviews` (
  `review_id` int NOT NULL AUTO_INCREMENT,
  `review_description` text NOT NULL,
  `rating` tinyint(1) NOT NULL,
  `user_id` int NOT NULL,
  `configuration_id` int NOT NULL,
  PRIMARY KEY (`review_id`),
  KEY `user_id_reviews_FK` (`user_id`),
  KEY `configuration_id_reviews_FK` (`configuration_id`),
  CONSTRAINT `configuration_id_reviews_FK` FOREIGN KEY (`configuration_id`) REFERENCES `car_configurations` (`configuration_id`),
  CONSTRAINT `user_id_reviews_FK` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reviews`
--

LOCK TABLES `reviews` WRITE;
/*!40000 ALTER TABLE `reviews` DISABLE KEYS */;
/*!40000 ALTER TABLE `reviews` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `suppliers`
--

DROP TABLE IF EXISTS `suppliers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `suppliers` (
  `supplier_id` int NOT NULL AUTO_INCREMENT,
  `supplier_name` varchar(30) NOT NULL,
  `supplier_location` varchar(30) NOT NULL,
  `supplier_website` text NOT NULL,
  `supplier_description` text NOT NULL,
  PRIMARY KEY (`supplier_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `suppliers`
--

LOCK TABLES `suppliers` WRITE;
/*!40000 ALTER TABLE `suppliers` DISABLE KEYS */;
/*!40000 ALTER TABLE `suppliers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_action_log`
--

DROP TABLE IF EXISTS `user_action_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user_action_log` (
  `log_id` int NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL,
  `action_type` varchar(255) NOT NULL,
  `action_timestamp` timestamp NOT NULL,
  `details` text NOT NULL,
  PRIMARY KEY (`log_id`),
  KEY `user_action_log_fk` (`user_id`),
  CONSTRAINT `user_action_log_fk` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user_action_log`
--

LOCK TABLES `user_action_log` WRITE;
/*!40000 ALTER TABLE `user_action_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `user_action_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `user_id` int NOT NULL AUTO_INCREMENT,
  `username` varchar(30) NOT NULL,
  `password_hash` char(64) NOT NULL,
  `name_user` varchar(30) NOT NULL,
  `level_of_access` varchar(20) NOT NULL,
  `actor_type` varchar(30) NOT NULL,
  `description` text,
  PRIMARY KEY (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-11-05 19:40:10