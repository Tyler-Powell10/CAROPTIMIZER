import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { HomepageComponent } from './homepage/homepage.component';
import { AccountInfoComponent } from './account-info/account-info.component';
import { ConfigureCarComponent } from './configure-car/configure-car.component';
import { GalleryComponent } from './gallery/gallery.component';
import { LoginComponent } from './login/login.component';
import { SupportTicketsComponent } from './support-tickets/support-tickets.component';
import { ViewPartsComponent } from './view-parts/view-parts.component';
import { SignupComponent } from './signup/signup.component';
import { RequestPartsComponent } from './request-parts/request-parts.component';
import { ReviewContentComponent } from './review-content/review-content.component';

const routes: Routes = [
  {path: 'home', component: HomepageComponent},
  {path: 'account', component: AccountInfoComponent},
  {path: 'carConfig', component: ConfigureCarComponent},
  {path: 'gallery', component: GalleryComponent},
  {path: 'login', component: LoginComponent},
  {path: 'support', component: SupportTicketsComponent},
  {path: 'parts', component: ViewPartsComponent},
  {path: 'signup', component: SignupComponent},
  {path: 'requestParts', component: RequestPartsComponent},
  {path: 'reviewContent', component: ReviewContentComponent},
  {path: '**', redirectTo: 'home'}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
