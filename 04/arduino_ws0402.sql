-- phpMyAdmin SQL Dump
-- version 4.2.10
-- http://www.phpmyadmin.net
--
-- Host: localhost:8889
-- Generation Time: 2015 年 8 月 04 日 17:45
-- サーバのバージョン： 5.5.38
-- PHP Version: 5.5.17

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `arduino_ws0402`
--
CREATE DATABASE IF NOT EXISTS `arduino_ws0402` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `arduino_ws0402`;

-- --------------------------------------------------------

--
-- テーブルの構造 `SeatTemps`
--

CREATE TABLE `SeatTemps` (
  `seattemps_index` int(11) NOT NULL,
  `seattemps_seatid` int(11) NOT NULL,
  `seattemps_temp` float NOT NULL,
  `seattemps_date` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `SeatTemps`
--
ALTER TABLE `SeatTemps`
 ADD PRIMARY KEY (`seattemps_index`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;