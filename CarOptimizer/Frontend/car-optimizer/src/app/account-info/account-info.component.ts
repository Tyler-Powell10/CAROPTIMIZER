import { Component, OnInit, OnDestroy } from '@angular/core';
import { AuthService } from '../services/auth.service';
import { UserType } from '../services/userType.service';
import { Subscription } from 'rxjs';

@Component({
  selector: 'app-account-info',
  templateUrl: './account-info.component.html',
  styleUrls: ['./account-info.component.css']
})

export class AccountInfoComponent {
  userInfo: any;
  user!: string;
  private subscription!: Subscription;
  
  constructor(private authService: AuthService, private userType: UserType) {}

  ngOnInit(): void {
    const userEmail = this.authService.getCurrentUserEmail();
    if (userEmail) {
      this.authService.getUserInfo(userEmail).subscribe(
        data => {
          this.userInfo = data;
          console.log(data);
        },
        error => {
          console.error('Error fetching user info', error);
        }
      );
    }

    //! this is to manually change users
    this.subscription = this.userType.currentAccountType.subscribe(
      (type: string) => {
        this.user = type;
      }
    );
    this.user = this.userType.getAccountType();
  }


  ngOnDestroy(): void {
    this.subscription.unsubscribe();
  }

  changeUserType(type: string): void {
    this.userType.changeAccountType(type);
  }

}













