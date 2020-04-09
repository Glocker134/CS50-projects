SELECT title FROM movies WHERE id IN
	(SELECT movie_id FROM stars WHERE person_id IN
		(SELECT id FROM people WHERE name LIKE 'johnny depp'))
AND id IN
	(SELECT movie_id FROM stars WHERE person_id IN
		(SELECT id FROM people WHERE name LIKE 'helena bonham carter'));