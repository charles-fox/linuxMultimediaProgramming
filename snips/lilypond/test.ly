\include "english.ly"
\header {
  title = \markup { "Exit Music" }
  composer = "Radiohead"
}

\markup  {VERSE1 VERSE2 CHORUS VERSE3 ENDING}
\markup {|}
\markup  {VERSE}
\score {


<<
  %chords with durations
  \chords { a1:m e1:/gsharp  c1:/g  d2:9/fsharp d2:m/f  a1:m e a:sus4 a }

  \relative c' {
                e4 r4 r4 f8 e8 |
                e4 r4 r4 r8 a,8 |
                e'4.( a,8) a4 e'4 |
                e2( d4.) d8 |

                c4 r4 r4 c8 c8 |
                b4 r4 r4 b8 b8( |
                b2) a4 r4 |
                r1 |

  }
  %one word per melody note
  \addlyrics { Wake from your sleep the drying of your tears, to- day we es- cape we es- cape}
>>


}

\markup  {CHORUS}
\score {
<<
	\chords{g:m11 g:m11 d:7 a:sus2 a:m e:sus4 e}
  
	\relative c' {
		\repeat volta 2 {

				bflat'2( a2 |
				g2.) g4 |
				a8 g8 fsharp2. |
				e2  e2 |
				e2 f4 e4 |
				e1 |	
				r1 |
		} 
	}

	\addlyrics{Breathe keep breathing don't loose your nerve}
>>
}


\markup  {ENDING}
\score {
<<	
	
	\chords{a:m b e f f bflat e e a:m e c d2 d2:m a1:m e a:sus4 a}
	
	\relative c' {
		c'2. e,4 | 
		eflat2. b'4 | 
		b2 d,2 | 
		d8 c8 r2 r8 f8 |

		\break 

		a2 c,2 | 
		d2 f2 | 
		e2 aflat2 | 
		d2 e4. e8 |

		\break

		e2. f8 e8 | 
		e2. e4 | 
		e4 d4 c4 e4 | 
		e2 d4. d8 |

		\break
		\repeat volta 2 {	
				c4 r4 r4 b8 c8 | 
				b4 r4 r4 b8 c8 | 
				b2 a2 | 
				r2 r4 r8 c8^"x3" |
		}
	}

	\addlyrics{You can laugh a spineless laugh}

>>
}


