-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE month=7 AND day=28 AND street="Chamberlin Street";
-- Trying to find out what happened after the theft incident.

SELECT name, transcript FROM interviews WHERE year=2020 AND month=7 AND day=28 AND name="Jose" OR name="Eugene" OR name="Barbara" OR name="Ruth" OR name="Raymond";
-- To read transcripts from the people that were related to the incident.

SELECT license_plate FROM courthouse_security_logs WHERE month=7 AND day=28 AND hour=10;
-- To check the cars that went out of the courthouse between 10.15 and 10.25

SELECT name, license_plate FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE month=7 AND day=28 AND transaction_type="withdraw" AND atm_location="Fifer Street"));
-- To get the names and license plates of the people that made atm withdrawal transactions on the same day as the theft incident.
-- This information, along with the courthouse logs, Ernest, Elizabeth, Danielle and Russell are suspicions

SELECT caller, receiver FROM phone_calls WHERE year=2020 AND day=28 AND month=7 AND duration<=60;
-- This takes phone calls that happened at the same day as the incident within a duration of <= 60.

SELECT name, phone_number FROM people WHERE name="Elizabeth" OR name="Ernest" OR name="Danielle" OR name="Russell";
-- To compare the phonecalls that took place during the theft and the phone numbers of these suspects.
-- This information leads with Ernest and Russell the only suspects left.

SELECT flight_id FROM passengers WHERE passport_number="5773159633";
-- Ernest flightids

SELECT flight_id FROM passengers WHERE passport_number="3592750733";
-- Russell flightids

SELECT id FROM flights WHERE year=2020 AND day=29 AND month=7 AND hour=8;
-- To check the flight ids that took place during 29 July 2020 at the earliest hour possible;
-- Kept changing the hour until hour8 gave a flight id, which is Ernest's. Which means Ernest is the thief.

SELECT name FROM people WHERE phone_number="(375) 555-8161";
-- To find out the name of the person that Ernest called after the theft.

SELECT city FROM airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE id=36);
-- To find out where Ernest escaped to.