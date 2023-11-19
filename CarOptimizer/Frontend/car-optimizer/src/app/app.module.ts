import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { NavbarComponent } from './navbar/navbar.component';
import { AccountInfoComponent } from './account-info/account-info.component';
import { ConfigureCarComponent } from './configure-car/configure-car.component';
import { GalleryComponent } from './gallery/gallery.component';
import { HomepageComponent } from './homepage/homepage.component';
import { LoginComponent } from './login/login.component';
import { SupportTicketsComponent } from './support-tickets/support-tickets.component';
import { ViewPartsComponent } from './view-parts/view-parts.component';
import { SignupComponent } from './signup/signup.component';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { RequestPartsComponent } from './request-parts/request-parts.component';
import { ReviewContentComponent } from './review-content/review-content.component';


@NgModule({
  declarations: [
    AppComponent,
    NavbarComponent,
    AccountInfoComponent,
    ConfigureCarComponent,
    GalleryComponent,
    HomepageComponent,
    LoginComponent,
    SupportTicketsComponent,
    ViewPartsComponent,
    SignupComponent,
    RequestPartsComponent,
    ReviewContentComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    FormsModule,
    HttpClientModule,
    ReactiveFormsModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
