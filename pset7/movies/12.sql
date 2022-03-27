SELECT title FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON movies.id = stars.movie_id WHERE name="Johnny Depp" INTERSECT SELECT title FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON movies.id = stars.movie_id WHERE name="Helena Bonham Carter"

-- Learned how to use the "INTERSECT" function through https://www.geeksforgeeks.org/sql-intersect-clause/#:~:text=The%20INTERSECT%20clause%20in%20SQL,both%20of%20the%20SELECT%20statements