-- phpMyAdmin SQL Dump
-- version 4.2.10
-- http://www.phpmyadmin.net
--
-- Host: localhost:8889
-- Generation Time: 2015 年 8 月 02 日 22:06
-- サーバのバージョン： 5.5.38
-- PHP Version: 5.5.17

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `arduino_ws0401`
--
CREATE DATABASE IF NOT EXISTS `arduino_ws0401` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `arduino_ws0401`;

-- --------------------------------------------------------

--
-- テーブルの構造 `Seats`
--

CREATE TABLE `Seats` (
`seats_index` int(11) NOT NULL,
  `seats_on` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=21 DEFAULT CHARSET=latin1;

--
-- テーブルのデータのダンプ `Seats`
--

INSERT INTO `Seats` (`seats_index`, `seats_on`) VALUES
(1, 0),
(2, 0),
(3, 0),
(4, 0),
(5, 0),
(6, 0),
(7, 0),
(8, 0),
(9, 0),
(10, 0),
(11, 0),
(12, 0),
(13, 0),
(14, 0),
(15, 0),
(16, 0),
(17, 0),
(18, 0),
(19, 0),
(20, 1);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Seats`
--
ALTER TABLE `Seats`
 ADD PRIMARY KEY (`seats_index`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Seats`
--
ALTER TABLE `Seats`
MODIFY `seats_index` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=21;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
