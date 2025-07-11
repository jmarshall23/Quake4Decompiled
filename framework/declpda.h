
// FUNC: public: __thiscall idDeclEmail::idDeclEmail(void)
void __thiscall idDeclEmail::idDeclEmail(idDeclEmail *this)
{
  this->__vftable = (idDeclEmail_vtbl *)&idDeclEmail::`vftable';
  this->base = 0;
  this->text.len = 0;
  this->text.alloced = 20;
  this->text.data = this->text.baseBuffer;
  this->text.baseBuffer[0] = 0;
  this->subject.alloced = 20;
  this->subject.len = 0;
  this->subject.data = this->subject.baseBuffer;
  this->subject.baseBuffer[0] = 0;
  this->date.alloced = 20;
  this->date.len = 0;
  this->date.data = this->date.baseBuffer;
  this->date.baseBuffer[0] = 0;
  this->to.alloced = 20;
  this->to.len = 0;
  this->to.data = this->to.baseBuffer;
  this->to.baseBuffer[0] = 0;
  this->from.alloced = 20;
  this->from.len = 0;
  this->from.data = this->from.baseBuffer;
  this->from.baseBuffer[0] = 0;
  this->image.alloced = 20;
  this->image.len = 0;
  this->image.data = this->image.baseBuffer;
  this->image.baseBuffer[0] = 0;
}

// FUNC: public: __thiscall idDeclVideo::idDeclVideo(void)
void __thiscall idDeclVideo::idDeclVideo(idDeclVideo *this)
{
  char *baseBuffer; // ecx

  this->__vftable = (idDeclVideo_vtbl *)&idDeclVideo::`vftable';
  this->base = 0;
  this->preview.len = 0;
  this->preview.alloced = 20;
  baseBuffer = this->preview.baseBuffer;
  this->preview.data = baseBuffer;
  *baseBuffer = 0;
  this->video.alloced = 20;
  this->video.len = 0;
  this->video.data = this->video.baseBuffer;
  this->video.baseBuffer[0] = 0;
  this->videoName.alloced = 20;
  this->videoName.len = 0;
  this->videoName.data = this->videoName.baseBuffer;
  this->videoName.baseBuffer[0] = 0;
  this->info.alloced = 20;
  this->info.len = 0;
  this->info.data = this->info.baseBuffer;
  this->info.baseBuffer[0] = 0;
  this->audio.alloced = 20;
  this->audio.len = 0;
  this->audio.data = this->audio.baseBuffer;
  this->audio.baseBuffer[0] = 0;
}

// FUNC: public: __thiscall idDeclPDA::idDeclPDA(void)
void __thiscall idDeclPDA::idDeclPDA(idDeclPDA *this)
{
  this->base = 0;
  this->__vftable = (idDeclPDA_vtbl *)&idDeclPDA::`vftable';
  this->videos.granularity = 16;
  this->videos.list = 0;
  this->videos.num = 0;
  this->videos.size = 0;
  this->audios.granularity = 16;
  this->audios.list = 0;
  this->audios.num = 0;
  this->audios.size = 0;
  this->emails.granularity = 16;
  this->emails.list = 0;
  this->emails.num = 0;
  this->emails.size = 0;
  this->pdaName.len = 0;
  this->pdaName.alloced = 20;
  this->pdaName.data = this->pdaName.baseBuffer;
  this->pdaName.baseBuffer[0] = 0;
  this->fullName.len = 0;
  this->fullName.alloced = 20;
  this->fullName.data = this->fullName.baseBuffer;
  this->fullName.baseBuffer[0] = 0;
  this->icon.len = 0;
  this->icon.alloced = 20;
  this->icon.data = this->icon.baseBuffer;
  this->icon.baseBuffer[0] = 0;
  this->id.len = 0;
  this->id.alloced = 20;
  this->id.data = this->id.baseBuffer;
  this->id.baseBuffer[0] = 0;
  this->post.len = 0;
  this->post.alloced = 20;
  this->post.data = this->post.baseBuffer;
  this->post.baseBuffer[0] = 0;
  this->title.len = 0;
  this->title.alloced = 20;
  this->title.data = this->title.baseBuffer;
  this->title.baseBuffer[0] = 0;
  this->security.alloced = 20;
  this->security.len = 0;
  this->security.data = this->security.baseBuffer;
  this->security.baseBuffer[0] = 0;
  this->originalVideos = 0;
  this->originalEmails = 0;
}
