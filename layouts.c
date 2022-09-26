static void tile(Monitor *);
static void monocle(Monitor *m);
static void centeredmaster(Monitor *m); /* ru_gaps layout */


void
tile(Monitor *m)
{
	unsigned int i, n, h, mw, my, ty, ns;
	float mfacts = 0, sfacts = 0;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++) {
		if (n < m->nmaster)
			mfacts += c->cfact;
		else
			sfacts += c->cfact;
	}
	if (n == 0)
		return;

	if (n > m->nmaster) {
		mw = m->nmaster ? m->ww * m->mfact : 0;
		ns = m->nmaster > 0 ? 2 : 1;
	} else {
		mw = m->ww;
		ns = 1;
	}
	for (i = 0, my = ty = m->gap->gappx, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
		if (i < m->nmaster) {
			// h = (m->wh - my) / (MIN(n, m->nmaster) - i) - gappx;
			h = (m->wh - my) * (c->cfact / mfacts) - m->gap->gappx;
			resize(c, m->wx + m->gap->gappx, m->wy + my, mw - (2 * c->bw) - m->gap->gappx * (5 - ns) / 2, h - (2 * c->bw), False);
			my += HEIGHT(c) + m->gap->gappx;
			mfacts -= c->cfact;
		} else {
			// h = (m->wh - ty) / (n - i) - gappx;
			h = (m->wh - ty) * (c->cfact / sfacts) - m->gap->gappx;
			resize(c, m->wx + mw + m->gap->gappx/ns, m->wy + ty, m->ww - mw - (2 * c->bw) - m->gap->gappx * (5 - ns) / 2, h - (2 * c->bw), False);
			ty += HEIGHT(c) + m->gap->gappx;
			sfacts -= c->cfact;
		}
}

void
monocle(Monitor *m)
{
	 unsigned int n = 0;
    Client *c;
 
    for (c = m->clients; c; c = c->next)
        if (ISVISIBLE(c))
            n++;
    if (n > 0) /* override layout symbol */
        snprintf(m->ltsymbol, sizeof m->ltsymbol, "[%d]", n);
    for (c = nexttiled(m->clients); c; c = nexttiled(c->next))
        resize(c, m->wx + m->gap->gappx, m->wy + m->gap->gappx, m->ww - 2 * c->bw - 2*m->gap->gappx, m->wh - 2 * c->bw - 2*m->gap->gappx, 0);

}

void
centeredmaster(Monitor *m)
{
	unsigned int i, n, h, mw, mx, my, oty, ety, tw;
	Client *c;
	
	/* count number of clients in the selected monitor */
	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	
	if (n == 0)
		return;
	if(n == 1){
		c = nexttiled(m->clients);
		resize(c, m->wx, m->wy, m->ww - 2 * c->bw, m->wh - 2 * c->bw, 0);
		return;
	}

	/* initialize areas */
	mw = m->ww;
	mx = 0;
	my = m->gap->gappx;
	tw = mw;

	if (n > m->nmaster) {
		/* go mfact box in the center if more than nmaster clients */
		mw = m->nmaster ? m->ww * m->mfact : 0;
		tw = m->ww - mw;

		if (n - m->nmaster > 1) {
			/* only one client */
			mx = (m->ww - mw) / 2;
			tw = (m->ww - mw) / 2;
		}
	}

	oty = m->gap->gappx;
	ety = m->gap->gappx;
	for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
	if (i < m->nmaster) {
		/* nmaster clients are stacked vertically, in the center
		 * of the screen */
		h = (m->wh - my) / (MIN(n, m->nmaster) - i);
		if(m->nmaster >= n)
			resize(c, m->wx + mx + m->gap->gappx, m->wy + my, mw - 2*(c->bw + m->gap->gappx),
		       h - (2*c->bw) - m->gap->gappx, 0);
		else if(m->nmaster + 1 < n)
			resize(c, m->wx + mx + m->gap->gappx/2, m->wy + my, mw - 2*c->bw - m->gap->gappx, h - 2*c->bw - m->gap->gappx, 0);
		else
			resize(c, m->wx + mx + m->gap->gappx, m->wy + my, mw - 2*c->bw - m->gap->gappx*3/2, h - 2*c->bw - m->gap->gappx, 0);
		if(my + HEIGHT(c) + m->gap->gappx < m->mh)
			my += HEIGHT(c) + m->gap->gappx;
	} else {
		/* stack clients are stacked vertically */
		if ((i - m->nmaster) % 2) {
			h = (m->wh - ety) / ( (1 + n - i) / 2);
			resize(c, m->wx + m->gap->gappx, m->wy + ety, tw - (2*c->bw) - m->gap->gappx*3/2, h - 2*c->bw - m->gap->gappx, 0);
			if(ety + HEIGHT(c) + m->gap->gappx < m->mh)
				ety += HEIGHT(c) + m->gap->gappx;
		} else {
			h = (m->wh - oty) / ((1 + n - i) / 2);
			resize(c, m->wx + mx + mw + m->gap->gappx/2, m->wy + oty, tw - (2*c->bw) - m->gap->gappx*3/2, h - 2*c->bw - m->gap->gappx, 0);
			if(oty + HEIGHT(c) + m->gap->gappx < m->mh)
				oty += HEIGHT(c) + m->gap->gappx;
		}
	}
}
